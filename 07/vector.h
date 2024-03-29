#include"Allocator.h"
#include"Iterator.h"
#include<memory>
#include<algorithm>
#include<stdexcept>

#pragma once
template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using iterator = Iterator<T>;
	using pointer = T*;
	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;

	Vector(size_type capacity = 0) :data_(alloc_.allocate(capacity)),size_(0),capacity_(capacity) {}
	Vector(size_type capacity, value_type value) :data_(alloc_.allocate(capacity)), size_(0), capacity_(capacity) {
		for (; size_ < capacity_; size_++) alloc_.construct(data_ + size_, value);
	}
	~Vector() {
		for (; size_ > 0; size_--) alloc_.destroy(data_ + size_ - 1);
		alloc_.deallocate(data_);
	}



	reference operator[](size_type pos) {
		return data_[pos];
	}
	const_reference operator[](size_type pos) const {
		return data_[pos];
	}

	void push_back(value_type&& value) {
		if (size_ == capacity_) {
			capacity_ = std::max(capacity_*2, size_type(1));
			auto newData = alloc_.allocate(capacity_);
			for (size_type s=0; s < size_; s++) {
				alloc_.construct(newData + s, data_[s]);
				alloc_.destroy(data_ + s);
			}
			swap(data_, newData);
			alloc_.deallocate(newData);
		}
		alloc_.construct(data_ + size_, value);
		size_++;
	}
	void push_back(const value_type& value) {
		if (size_ == capacity_) {
			capacity_ = std::max(capacity_*2, size_type(1));
			auto newData = alloc_.allocate(capacity_);
			for (size_type s=0; s < size_; s++) {
				alloc_.construct(newData + s, data_[s]);
				alloc_.destroy(data_ + s);
			}
			std::swap(data_, newData);
			alloc_.deallocate(newData);

		}
		alloc_.construct(data_ + size_, value);
		size_++;
	}

	void pop_back() {
		if (size_ == 0) throw std::runtime_error("No elements to remove");
		size_--;
		alloc_.destroy(data_ + size_);
	}

	bool empty() const {
		return size_ == 0;
	}

	size_type size() const {
		return size_;
	}

	void clear() {
		while (size_ != 0) alloc_.destroy(data_ + --size_);
	}

	void resize(size_type count, value_type value=value_type()) {
		if (count > capacity_) {
			capacity_ = std::max(capacity_*2, count);
			auto newData = alloc_.allocate(capacity_);
			for (size_type s=0; s < size_; s++) {
				alloc_.construct(newData + s, data_[s]);
				alloc_.destroy(data_ + s);
			}
			std::swap(data_, newData);
			alloc_.deallocate(newData);
			for (; size_ < count; size_++) alloc_.construct(data_ + size_, value);
		}
		else if (count > size_) {
			for (; size_ < count; size_++) alloc_.construct(data_ + size_, value);
		}
		else {
			for (; size_ > count; size_--) alloc_.destroy(data_ + size_ - 1);
		}
	}

	void reserve(size_type count) {
		if (count <= capacity_) return;
		capacity_ = count;
		auto newData = alloc_.allocate(capacity_);
		for (size_type s=0; s < size_; s++) {
			alloc_.construct(newData + s, data_[s]);
			alloc_.destroy(data_ + s);
		}
		swap(data_, newData);
		alloc_.deallocate(newData);
	}

	Iterator<T> begin() {
		return Iterator<T>(data_);
	}
	Iterator<T> end() {
		return Iterator<T>(data_+size_);
	}

	rIterator<T> rbegin() {
		return rIterator<T>(data_ + size_ - 1);
	}
	rIterator<T> rend() {
		return rIterator<T>(data_ - 1);
	}

	const Iterator<const T> begin() const {
		return Iterator<const T>(data_);
	}
	const Iterator<const T> end() const {
		return Iterator<const T>(data_ + size_);
	}

	const rIterator<const T> rbegin() const {
		return rIterator<const T>(data_ + size_ - 1);
	}
	const rIterator<const T> rend() const {
		return rIterator<const T>(data_ - 1);
	}

private:
	Alloc alloc_;
	pointer data_;
	size_type size_, capacity_;
};
