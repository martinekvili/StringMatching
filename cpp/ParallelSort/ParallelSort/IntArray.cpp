#include "IntArray.h"

using namespace tbb;

IntArray::IntArray(int size, bool fillWithRandom)
{
	arr = new int[size];
	this->size = size;

	if (fillWithRandom)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = rand() % 1000;
		}
	}
}

void IntArray::copy(int* src, int start, int length, int* dest) {
	for (int i = 0; i < length; i++) {
		dest[i] = src[start + i];
	}
}

void IntArray::sort(int depth)
{
	if (depth == 0) {
		std::sort(arr, arr + size);
	}
	else {
		SortTask& t = *new(task::allocate_root()) SortTask(arr, size, depth);
		task::spawn_root_and_wait(t);
	}
}

void IntArray::init() {
	srand(time(NULL));
}

IntArray::~IntArray() {
	delete[] arr;
}

std::ostream& operator<<(std::ostream& os, const IntArray& arr) {
	for (size_t i = 0; i < arr.size; i++) {
		os << arr.arr[i] << " ";
	}
	os << std::endl;
	return os;
}

task* IntArray::SortTask::execute() {
	if (depth == 0) {
		std::sort(whole, whole + length);
	}
	else {
		int *firstHalf = new int[length / 2];
		int *secondHalf = new int[length / 2];
		IntArray::copy(whole, 0, length / 2, firstHalf);
		IntArray::copy(whole, length / 2, length / 2, secondHalf);


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
			else if (firstHalf[i] < secondHalf[j])
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


