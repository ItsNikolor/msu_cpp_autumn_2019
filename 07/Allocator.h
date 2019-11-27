#include<memory>
#include<algorithm>
#include<stdexcept>

#pragma once

template <class T>
class Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;
	using const_reference = const T&;

	size_type size_ = 0, capacity_;
	std::unique_ptr<value_type[]> data_;

	Allocator(size_type capacity = 0) : data_(new value_type[capacity]), capacity_(capacity) {}
	Allocator(size_type capacity, value_type value) : data_(new value_type[capacity]), capacity_(capacity), size_(capacity) {
		for (int i = 0; i < capacity; i++) {
			data_[i] = value;
		}
	}

	pointer allocate(size_type count) {
		if (count + size_ > capacity_) {
			if (capacity_ * 2 > count + size_) capacity_ *= 2;
			else capacity_ = count + size_;
			auto newData = std::make_unique<T[]>(capacity_);
			std::copy(data_.get(), data_.get() + size_, newData.get());
			data_.swap(newData);
		}
		size_ += count;
		return data_.get() + size_ - count;
	}

	void deallocate(size_type count) {
		if (count > size_) throw std::runtime_error("No elements to delete");
		for (int i = count - 1; i > size_ - count; i--) {
			value_type trash;
			trash = std::move(data_[i]);
		}
		size_ -= count;
	}

	void resize(size_type count, value_type value) {
		if (count > capacity_) {
			size_type dif = count - size_;
			auto p = allocate(dif);
			for (size_type i = 0; i < dif; i++) p[i] = value;
		}
		else if (count > size_) {
			for (size_type i = size_; i < count; i++) data_[i] = value;
			size_ = count;
		}
		else {
			deallocate(size_ - count);
		}
	}

	void reserve(size_type count) {
		if (count <= capacity_) return;
		auto newData = std::make_unique<value_type[]>(count);
		std::copy(data_.get(), data_.get() + size_, newData.get());
		data_.swap(newData);
	}

	size_t max_size() const noexcept {
		return capacity_;
	}
};
