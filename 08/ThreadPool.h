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
	std::condition_variable c;
	std::vector<std::thread> threads;

	size_t _poolSize;
	
	bool KeepWorking = true;

	void ThreadWork() {
		while (KeepWorking||_work.size()!=1) {
			std::unique_lock<std::mutex> l(m);

			c.wait(l, [this]() {return !(_work.empty()&&KeepWorking); });
			if (!KeepWorking) break;

			auto work = std::move(_work.front());
			_work.pop_front();

			l.unlock();
			work();

		}
	}
public:
	explicit ThreadPool(size_t poolSize):_poolSize(poolSize) {
		for (size_t i = 0; i < poolSize; i++) {
			threads.emplace_back([this]() {ThreadWork(); });
		}
	}

	~ThreadPool() {
		std::unique_lock<std::mutex> l(m);

		KeepWorking = false;

		c.notify_all();
		l.unlock();
		
		for (auto& t : threads) t.join();
	}

	// pass arguments by value
	template <class Func, class... Args>
	auto exec(Func func, Args... args)->std::future<decltype(func(args...))> {
		using T = decltype(func(args...));
		auto f = std::bind(func, std::forward<Args>(args)...);

		std::shared_ptr<std::promise<T>> p(new std::promise<T>);

		std::function<void()> ff = [f, p]() {p->set_value(f()); };
		
		std::function<void()> fff = [ff]() {ff(); };

		{
			std::unique_lock<std::mutex> l(m);

			_work.emplace_back(fff);
		}
		c.notify_one();
		return p->get_future();
	}
};
