#ifndef StringSorter_H
#define StringSorter_H

#include <algorithm>

#include "tbb/tbb.h"
#include "tbb/task.h"

struct StringComparer {
	bool operator() (const char *one, const char *other) const {
		return strcmp(one, other) < 0;
	}
};

class StringSorter
{
	StringSorter(const StringSorter& other);
	StringSorter& operator=(const StringSorter& other);

public:
	static void copy(char **src, int start, int length, char **dest);

	static void sort(char ** array, size_t length, int depth = 0);

	class SortTask : public tbb::task 
	{
		char ** whole;
		size_t length;
		int depth;

	public:

		SortTask(char **s, size_t l, int d) : whole(s), length(l), depth(d) {}

		tbb::task* execute();
	};
};

#endif