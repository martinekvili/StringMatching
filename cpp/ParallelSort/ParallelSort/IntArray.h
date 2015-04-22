#ifndef INTARRAY_H
#define INTARRAY_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tbb/tbb.h"
#include "tbb/task.h"

class IntArray
{
	int* arr;
	size_t size;

	IntArray(const IntArray& other);
	IntArray& operator=(const IntArray& other);

	static void copy(int* src, int start, int length, int* dest);

public:

	IntArray(int size, bool fillWithRandom = false);

	void sort(int depth = 0);

	static void init();

	~IntArray();

	friend std::ostream& operator<<(std::ostream& os, const IntArray& arr);

	class SortTask : public tbb::task 
	{
		int* whole;
		size_t length;
		int depth;

	public:

		SortTask(int *s, size_t l, int d) : whole(s), length(l), depth(d) {}

		tbb::task* execute();
	};
};

std::ostream& operator<<(std::ostream& os, const IntArray& arr);

#endif