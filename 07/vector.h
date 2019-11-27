#include"Allocator.h"
#include"Iterator.h"

#pragma once
template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using iterator = Iterator<T>;
	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;

	Vector(size_type capacity = 0) :alloc_(capacity) {}
	Vector(size_type capacity, value_type value) :alloc_(capacity, value) {}



	reference operator[](size_type pos) {
		return alloc_.data_[pos];
	}
	const_reference operator[](size_type pos) const {
		return alloc_.data_[pos];
	}

	void push_back(value_type&& value) {
		*alloc_.allocate(1) = value;
	}
	void push_back(const value_type& value) {
		*alloc_.allocate(1) = value;
	}

	void pop_back() {
		alloc_.deallocate(1);
	}

	bool empty() const {
		return alloc_.size_ == 0;
	}

	size_type size() const {
		return alloc_.size_;
	}

	void clear() {
		alloc_.deallocate(alloc_.size_);
	}

	void resize(size_type count, value_type value=value_type()) {
		alloc_.resize(count, value);
	}

	void reserve(size_type count) {
		alloc_.reserve(count);
	}

	Iterator<T> begin() {
		return Iterator<T>(alloc_.data_.get());
	}
	Iterator<T> end() {
		return Iterator<T>(alloc_.data_.get()+alloc_.size_);
	}

	rIterator<T> rbegin() {
		return rIterator<T>(alloc_.data_.get() + alloc_.size_ - 1);
	}
	rIterator<T> rend() {
		return rIterator<T>(alloc_.data_.get() - 1);
	}

	const Iterator<const T> begin() const {
		return Iterator<const T>(alloc_.data_.get());
	}
	const Iterator<const T> end() const {
		return Iterator<const T>(alloc_.data_.get() + alloc_.size_);
	}

	const rIterator<const T> rbegin() const {
		return rIterator<const T>(alloc_.data_.get() + alloc_.size_ - 1);
	}
	const rIterator<const T> rend() const {
		return rIterator<const T>(alloc_.data_.get() - 1);
	}

private:
	Alloc alloc_;
};
