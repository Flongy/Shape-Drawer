#include "MemoryCheck.h"
#include <iostream>

#ifdef WINDOWS

#include <stdlib.h>
#include <crtdbg.h>

void prepareMemoryCheck() {
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}

void printMemoryUsage() {
	std::cout << "====================\n";
	_CrtMemState state;
	_CrtMemCheckpoint(&state);
	_CrtMemDumpStatistics(&state);
	std::cout << "====================\n";
}

void endMemoryDump() {
	auto leak_found = _CrtDumpMemoryLeaks();
	if (!leak_found)
		std::puts("No memory leaks found in this application!");
}

#else

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

void prepareMemoryCheck() {
	CURRENT_MEMORY_USAGE = 0;
}

void printMemoryUsage() {
	std::cout << "Currently " << CURRENT_MEMORY_USAGE << " bytes allocated to the program\n";
}

void endMemoryDump() {
	std::cout << "Memory usage at the end: " << CURRENT_MEMORY_USAGE << " bytes. ";
	if (CURRENT_MEMORY_USAGE > 0)
		std::cout << "WARNING: Not all memory was deallocated.";

	std::cout << std::endl;
}
#endif
