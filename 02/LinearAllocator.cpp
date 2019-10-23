#include<iostream>
#include"LinearAllocator.h"


LinearAllocator::LinearAllocator(size_t maxSize):maxSize(maxSize){
	if(maxSize!=0) allmemory = new char[maxSize];
	else allmemory=nullptr;
}

char* LinearAllocator::alloc(size_t size){
	if (offset + size > maxSize||size==0) return nullptr;
	else {
		char* p = &allmemory[offset];
		offset += size;
		return p;
	}
}
void LinearAllocator::reset() {
	offset = 0;
}

LinearAllocator::~LinearAllocator(){
	if(maxSize!=0) delete[]allmemory;
}
