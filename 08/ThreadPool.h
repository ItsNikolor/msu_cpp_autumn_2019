#pragma once
#include<iostream>
#include<thread>
#include<future>
#include<vector>
#include<deque>
#include<iostream>
#include <functional>


template<class T>
class myFuture {
	friend class ThreadPool;
	std::unique_ptr<std::promise<T>> promise;
	std::future<T> future;
	myFuture() :promise(new std::promise<T>), future(promise->get_future()) {}

public:
	T get() { return future.get(); }
	myFuture(myFuture&& obj) noexcept {
		promise = std::move(obj.promise);
		future = std::move(obj.future);
	}
};

class ThreadPool {
	std::deque<std::function<void()>> _work;
	std::mutex m, m_exit;
	std::condition_variable c, c_exit;

	size_t _poolSize;
	int dead = 0;
	std::atomic<bool>  KeepWorking = true;

	void ThreadWork() {
		while (KeepWorking) {
			std::unique_lock<std::mutex> l(m);

			//while (_work.empty() && KeepWorking)
			c.wait(l, [this]() {return !(_work.empty() && KeepWorking); });
			if (!KeepWorking) break;

			auto work = std::move(_work.front());
			_work.pop_front();
			l.unlock();

			work();
		}
		std::unique_lock<std::mutex> l(m);
		dead++;
		if (dead == _poolSize) c_exit.notify_one();
		std::cout << std::this_thread::get_id() << " Died\n";
	}
public:
	explicit ThreadPool(size_t poolSize):_poolSize(poolSize) {
		
		for (size_t i = 0; i < poolSize; i++) {
			std::thread t([this]() {ThreadWork(); });
			t.detach();
		}
	}

	~ThreadPool() {
		KeepWorking = false;
		c.notify_all();
		std::unique_lock<std::mutex> l(m);
		//while (dead != _poolSize) 
		c_exit.wait(l, [this]() {return dead == _poolSize; });
		//std::unique_lock<std::mutex> l(m);
		std::cout << std::this_thread::get_id() << " Died\n";
	}

	// pass arguments by value
	template <class Func, class... Args>
	auto exec(Func func, Args... args)->myFuture<decltype(func(args...))> {
		using T = decltype(func(args...));
		auto f = std::bind(func, std::forward<Args>(args)...);
		myFuture<T> obj;

		std::function<void(std::promise<T>*)> ff = [f](std::promise<T>* p) {p->set_value(f()); };

		std::function<void()> fff = std::bind(ff, obj.promise.get());

		{
			std::unique_lock<std::mutex> l(m);

			_work.emplace_back(fff);
		}
		c.notify_one();
		return obj;
	}
};
	