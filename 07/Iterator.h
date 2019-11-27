#pragma once
template <class T>
class Iterator {
	T* ptr_;
public:
	explicit Iterator(T* ptr) : ptr_(ptr) {}

	bool operator==(const Iterator<T>& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) const {
		return !(*this == other);
	}

	T& operator*() const {
		return *ptr_;
	}

	Iterator& operator++() {
		++ptr_;
		return *this;
	}

	Iterator& operator--() {
		--ptr_;
		return *this;
	}

	Iterator operator+(int offset) const {
		return Iterator(ptr_ + offset);
	}

	Iterator operator-(int offset) const {
		return Iterator(ptr_ - offset);
	}

	int operator-(const Iterator<T>& it) const {
		return ptr_ - it.ptr_;
	}

};

template<class T>
Iterator<T> operator+(int offset, const Iterator<T>& it) {
	return it + offset;
}

template <class T>
class rIterator {
	T* ptr_;
public:
	explicit rIterator(T* ptr) : ptr_(ptr) {}

	bool operator==(const rIterator<T>& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator!=(const rIterator<T>& other) const {
		return !(*this == other);
	}

	T& operator*() const {
		return *ptr_;
	}

	rIterator& operator++() {
		--ptr_;
		return *this;
	}

	rIterator& operator--() {
		++ptr_;
		return *this;
	}

	rIterator operator+(int offset) const {
		return rIterator(ptr_ - offset);
	}

	rIterator operator-(int offset) const {
		return rIterator(ptr_ + offset);
	}

	int operator-(const rIterator<T>& it) const {
		return ptr_ + it.ptr_;
	}

};

template<class T>
rIterator<T> operator+(int offset, const rIterator<T>& it) {
	return it - offset;
}

template<class T>
bool operator==(const Iterator<T>& it, const rIterator<T>& rit) {
	return it.ptr_ == rit.ptr_;
}

template<class T>
bool operator==(const rIterator<T>& rit, const Iterator<T>& it) {
	return it.ptr_ == rit.ptr_;
}

template<class T>
bool operator!=(const Iterator<T>& it, const rIterator<T>& rit) {
	return it.ptr_ != rit.ptr_;
}

template<class T>
bool operator!=(const rIterator<T>& rit, const Iterator<T>& it) {
	return it.ptr_ != rit.ptr_;
}