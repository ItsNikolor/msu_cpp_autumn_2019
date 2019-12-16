#pragma once
#include<iostream>
#include<fstream>
#include<thread>
#include<vector>
#include<mutex>
#include<functional>
#include<algorithm>
#include<queue>

void sort_file(const char* in_path, const char* output_path, const char* tmp_path = "tmp.dat", size_t num_threads = 2) {
	std::ifstream in_file(in_path, std::ios::binary);
	if (!in_file) 
		throw(std::exception("Can't open input file\n"));
	

	std::ofstream out_file(output_path, std::ios::binary);
	if (!out_file) 
		throw(std::exception("Can't open output file\n"));
	

	std::ofstream tmp_file(tmp_path, std::ios::binary);
	if (!tmp_file)
		throw(std::exception("Can't open tmp file\n"));
	

	std::mutex read, write;
	const size_t memory_size = 4194304;// 4 ьс
	static auto thread_func_lambda = [memory_size](std::mutex& read, std::mutex& write,
		std::ifstream& in_file, std::ofstream& tmp_file) {

			std::unique_ptr<uint64_t[]> a(new uint64_t[memory_size / sizeof(uint64_t)]);
			while (true) {
				std::unique_lock<std::mutex> lock_read(read);
				in_file.read((char*)a.get(), memory_size);
				size_t read_count = in_file.gcount();
				lock_read.unlock();

				if (read_count == 0) break;
				std::sort(a.get(), a.get() + read_count / sizeof(uint64_t));

				std::unique_lock<std::mutex> lock_write(write);
				tmp_file.write((char*)&read_count, sizeof(size_t));
				tmp_file.write((char*)a.get(), read_count);
			}
	};
	std::vector<std::thread> threads(num_threads);
	auto thread_func = bind(thread_func_lambda, std::ref(read), std::ref(write), std::ref(in_file), std::ref(tmp_file));
	while (num_threads) threads[--num_threads] = std::thread(thread_func);

	for (auto& t : threads) t.join();

	tmp_file.close();
	in_file.close();

	in_file.open(tmp_path, std::ios::binary);
	if (!in_file) 
		throw(std::exception("Can't open tmp file\n"));
	

	struct Triple {
		uint64_t val, pos, max;
		Triple(uint64_t val_, uint64_t pos_, uint64_t max_) :val(val_), pos(pos_), max(max_) {};
		bool operator>(const Triple& A) const {
			return val > A.val;
		}
	};
	using T = Triple;
	std::priority_queue<T, std::vector<T>, std::greater<T>> que;
	size_t i = 0;

	while (true) {
		uint64_t tmp;
		size_t count;

		if (!in_file.read((char*)&count, sizeof(size_t))) break;
		in_file.read((char*)&tmp, sizeof(uint64_t));

		que.emplace(T( tmp, in_file.tellg(), (uint64_t)in_file.tellg() + count - sizeof(uint64_t) ));
		in_file.seekg(count - sizeof(uint64_t), std::ios::cur);
	}
	in_file.clear();

	while (!que.empty()) {

		auto smallest = que.top();
		auto smallest_val = smallest.val;
		auto smallest_pos = smallest.pos;
		auto smallest_max = smallest.max;
		que.pop();

		out_file.write((char*)&smallest_val, sizeof(uint64_t));
		if (smallest_pos >= smallest_max) continue;

		in_file.seekg(smallest_pos);
		uint64_t tmp;

		in_file.read((char*)&tmp, sizeof(uint64_t));
		que.emplace(T( tmp,smallest_pos + sizeof(uint64_t),smallest_max ));
	}
}
