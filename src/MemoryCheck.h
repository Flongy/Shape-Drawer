#pragma once

#include <iostream>

static std::size_t CURRENT_MEMORY_USAGE = 0;

void* operator new(std::size_t size) {

	if (void* ptr = malloc(size)) {
		CURRENT_MEMORY_USAGE += size;
		return ptr;
	}

	throw std::bad_alloc{};
}

void operator delete(void* ptr, std::size_t size) {
	CURRENT_MEMORY_USAGE -= size;
	std::free(ptr);
}

void printMemoryUsage() {
	std::cout << "Currently " << CURRENT_MEMORY_USAGE << " bytes allocated to the program\n";
}
