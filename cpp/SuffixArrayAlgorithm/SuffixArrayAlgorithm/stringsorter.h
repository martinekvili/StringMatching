#ifndef STRINGSORTER_H
#define STRINGSORTER_H

#include <algorithm>
#include <functional>

#include "tbb/tbb.h"
#include "tbb/task.h"

struct StringSorter
{
	StringSorter(const StringSorter& other) = delete;
	StringSorter& operator=(const StringSorter& other) = delete;

	static void copy(int *src, int start, int length, int *dest);

	static void sort(const char *str, int* array, int length, int depth = 0);

	class SortTask : public tbb::task 
	{
		std::function<bool(int, int)> comp;
		int* whole;
		int length;
		int depth;

	public:
		SortTask(std::function<bool(int, int)> comp, int *s, int l, int d) :
			comp(comp), whole(s), length(l), depth(d) {}

		tbb::task* execute();
	};
};

#endif