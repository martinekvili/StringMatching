#include "stringsorter.h"

void StringSorter::copy(int *src, int start, int length, int *dest) {
	for (int i = 0; i < length; i++) {
		dest[i] = src[start + i];
	}
}

void StringSorter::sort(const char *str, int* arr, int length, int depth)
{
	auto comp = [str](int one, int other) {
		return strcmp(str + one, str + other) < 0;
	};

	if (depth == 0) {
		std::sort(arr, arr + length, comp);
	}
	else {
		SortTask& t = *new(tbb::task::allocate_root()) SortTask(comp, arr, length, depth);
		tbb::task::spawn_root_and_wait(t);
	}
}

tbb::task* StringSorter::SortTask::execute() {
	if (depth == 0) {
		std::sort(whole, whole + length, comp);
	}
	else {
		int firstLength = length / 2;
		int secondLength = length - firstLength;

		int *firstHalf = new int[firstLength];
		int *secondHalf = new int[secondLength];
		StringSorter::copy(whole, 0, length / 2, firstHalf);
		StringSorter::copy(whole, firstLength, secondLength, secondHalf);


		SortTask& a = *new(allocate_child()) SortTask(comp, firstHalf, firstLength, depth - 1);
		SortTask& b = *new(allocate_child()) SortTask(comp, secondHalf, secondLength, depth - 1);
		// Set ref_count to 'two children plus one for the wait".
		set_ref_count(3);
		// Start b running.
		spawn(b);
		// Start a running and wait for all children (a and b).
		spawn_and_wait_for_all(a);

		size_t i = 0, j = 0, k = 0;
		while (i < firstLength || j < secondLength)
		{
			if (i == firstLength)
			{
				whole[k] = secondHalf[j++];
			}
			else if (j == secondLength)
			{
				whole[k] = firstHalf[i++];
			}
			else if (comp(firstHalf[i], secondHalf[j]))
			{
				whole[k] = firstHalf[i++];
			}
			else
			{
				whole[k] = secondHalf[j++];
			}
			k++;
		}

		delete firstHalf;
		delete secondHalf;
	}

	return nullptr;
}


