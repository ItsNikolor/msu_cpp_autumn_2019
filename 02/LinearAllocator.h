#pragma once
class LinearAllocator{
public:
	LinearAllocator(size_t maxSize = 100);
	char* alloc(size_t size);
	void reset();
	~LinearAllocator();
private:
	char* allmemory;
	size_t maxSize, offset = 0;
};