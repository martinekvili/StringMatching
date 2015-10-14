#ifndef MERGE_HPP
#define MERGE_HPP

#include <algorithm>
#include <functional>

#include "tbb\tbb.h"

template <typename T>
class MergeSort {
	static const int mergeTreshold;
	static const int sortTreshold;

public:
	using Comparator = std::function<bool(T, T)>;

private:
	static void sequentialMerge(T* arr1, T* end1, T* arr2, T* end2, T* dst, Comparator comp) {
		while (arr1 != end1 && arr2 != end2) {
			if (comp(*arr1, *arr2)) {
				*dst = *arr1;
				arr1++;
			}
			else {
				*dst = *arr2;
				arr2++;
			}
			dst++;
		}

		while (arr1 != end1) {
			*dst = *arr1;
			dst++;
			arr1++;
		}

		while (arr2 != end2) {
			*dst = *arr2;
			dst++;
			arr2++;
		}
	}

	static void parallelMerge(T* arr, int start1, int end1, int start2, int end2, T* dst, int pos, Comparator comp) {
		int length1 = end1 - start1;
		int length2 = end2 - start2;

		if (length1 < length2) {
			std::swap(start1, start2);
			std::swap(end1, end2);
			std::swap(length1, length2);
		}

		if (length1 == 0) {
			return;
		}

		if ((length1 + length2) < mergeTreshold) {
			sequentialMerge(arr + start1, arr + end1, arr + start2, arr + end2, dst + pos, comp);
		}
		else {
			int xpos1 = (start1 + end1) / 2;
			int xpos2 = (int) (std::lower_bound(arr + start2, arr + end2, arr[xpos1], comp) - arr);
			int xpos_dst = pos + (xpos1 - start1) + (xpos2 - start2);

			dst[xpos_dst] = arr[xpos1];

			tbb::parallel_invoke(
					[=]() { parallelMerge(arr, start1, xpos1, start2, xpos2, dst, pos, comp); },
					[=]() { parallelMerge(arr, xpos1 + 1, end1, xpos2, end2, dst, xpos_dst + 1, comp); }
				);
		}
	}

	static void parallelSort(T* src, int start, int end, T* dest, Comparator comp, bool srcToDest = false) {
		if (start == end) {
			return;
		}

		if ((end - start) < sortTreshold) {
			std::sort(src + start, src + end, comp);

			if (srcToDest) {
				for (int i = start; i < end; i++) {
					dest[i] = src[i];
				}
			}

			return;
		}

		int middle = (start + end) / 2;
		tbb::parallel_invoke(
				[=]() { parallelSort(src, start, middle, dest, comp, !srcToDest); },
				[=]() { parallelSort(src, middle, end, dest, comp, !srcToDest); }
			);

		if (srcToDest) {
			parallelMerge(src, start, middle, middle, end, dest, start, comp);
		}
		else {
			parallelMerge(dest, start, middle, middle, end, src, start, comp);
		}
	}

public:
	static void parallelSort(T *arr, int length, Comparator comp) {
		T* acc = new T[length];

		parallelSort(arr, 0, length, acc, comp);

		delete[] acc;
	}
};

template <typename T>
const int MergeSort<T>::mergeTreshold = 8192;

template <typename T>
const int MergeSort<T>::sortTreshold = 48;

#endif