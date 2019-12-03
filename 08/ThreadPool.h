#pragma once
#include<iostream>
#include<thread>
#include<future>
#include<vector>
#include<deque>
#include <functional>

class ThreadPool {
	std::deque<std::function<void()>> _work;
	std::mutex m;
	std::condition_variable c, c_exit;

	size_t _poolSize;
	
	
	volatile int dead = 0;
	volatile bool KeepWorking = true;

	void ThreadWork() {
		while (KeepWorking||_work.size()!=1) {
			std::unique_lock<std::mutex> l(m);

			c.wait(l, [this]() {return !(_work.empty()); });
			if (!KeepWorking && _work.size() == 1) break;

			auto work = std::move(_work.front());
			_work.pop_front();

			l.unlock();
			work();

		}
		std::unique_lock<std::mutex> l(m);
		dead++;
		if (dead == _poolSize) c_exit.notify_one();
		std::cout << "Tread " << std::this_thread::get_id() << " Died\n";
	}
public:
	explicit ThreadPool(size_t poolSize):_poolSize(poolSize) {
		for (size_t i = 0; i < poolSize; i++) {
			std::thread t([this]() {ThreadWork(); });
			t.detach();
		}
	}

	~ThreadPool() {
		std::unique_lock<std::mutex> l(m);
		_work.push_back([]() {});
		KeepWorking = false;
		c.notify_all();
		
		c_exit.wait(l, [this]() {return dead == _poolSize; });
		
		std::cout << "Main tread "<<std::this_thread::get_id() << " died\n";
		std::cout << "---------------------------------------------\n\n\n";
	}

	// pass arguments by value
	template <class Func, class... Args>
	auto exec(Func func, Args... args)->std::future<decltype(func(args...))> {
		using T = decltype(func(args...));
		auto f = std::bind(func, std::forward<Args>(args)...);
		std::unique_ptr<std::promise<T>> p(new std::promise<T>);


		std::function<void(std::promise<T>*)> ff = [f](std::promise<T>* p) {p->set_value(f()); delete p; };

		std::function<void()> fff = std::bind(ff, p.get());

		{
			std::unique_lock<std::mutex> l(m);

			_work.emplace_back(fff);
		}
		c.notify_one();
		return p.release()->get_future();
	}
};
