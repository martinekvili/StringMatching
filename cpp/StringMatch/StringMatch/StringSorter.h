#ifndef StringSorter_H
#define StringSorter_H

#include <algorithm>

#include "tbb/tbb.h"
#include "tbb/task.h"

class StringComparer {
	const char *str;

public:
	bool operator() (const int one, const int other) const {
		return strcmp(str + one, str + other) < 0;
	}

	StringComparer(const char *s) : str(s) {}
};

class StringSorter
{
	StringSorter(const StringSorter& other);
	StringSorter& operator=(const StringSorter& other);

public:
	static void copy(int *src, int start, int length, int *dest);

	static void sort(const char *str, int* array, size_t length, int depth = 0);

	class SortTask : public tbb::task 
	{
		const char *str;
		int* whole;
		size_t length;
		int depth;

	public:

		SortTask(const char *orig, int *s, size_t l, int d) : str(orig), whole(s), length(l), depth(d) {}

		tbb::task* execute();
	};
};

#endif