#include "StringSorter.h"

using namespace tbb;

void StringSorter::copy(char **src, int start, int length, char **dest) {
	for (int i = 0; i < length; i++) {
		dest[i] = src[start + i];
	}
}

void StringSorter::sort(char ** arr, size_t length, int depth)
{
	if (depth == 0) {
		std::sort(arr, arr + length, StringComparer());
	}
	else {
		SortTask& t = *new(task::allocate_root()) SortTask(arr, length, depth);
		task::spawn_root_and_wait(t);
	}
}

task* StringSorter::SortTask::execute() {
	StringComparer comp;

	if (depth == 0) {
		std::sort(whole, whole + length, comp);
	}
	else {
		char **firstHalf = new char*[length / 2];
		char **secondHalf = new char*[length / 2];
		StringSorter::copy(whole, 0, length / 2, firstHalf);
		StringSorter::copy(whole, length / 2, length / 2, secondHalf);


		SortTask& a = *new(allocate_child()) SortTask(firstHalf, length / 2, depth - 1);
		SortTask& b = *new(allocate_child()) SortTask(secondHalf, length / 2, depth - 1);
		// Set ref_count to 'two children plus one for the wait".
		set_ref_count(3);
		// Start b running.
		spawn(b);
		// Start a running and wait for all children (a and b).
		spawn_and_wait_for_all(a);

		size_t i = 0, j = 0, k = 0;
		while (i < length / 2 || j < length / 2)
		{
			if (i == length / 2)
			{
				whole[k] = secondHalf[j++];
			}
			else if (j == length / 2)
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
	return NULL;
}


