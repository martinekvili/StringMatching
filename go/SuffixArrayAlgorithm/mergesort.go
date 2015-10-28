package main

import "sort"

func sequentialMerge(arr1 []string, arr2 []string, dst []string) {
	idx1 := 0
	idx2 := 0
	idx_dst := 0

	for idx1 < len(arr1) && idx2 < len(arr2) {
		if arr1[idx1] < arr2[idx2] {
			dst[idx_dst] = arr1[idx1]
			idx1++
		} else {
			dst[idx_dst] = arr2[idx2]
			idx2++
		}
		idx_dst++
	}

	for idx1 < len(arr1) {
		dst[idx_dst] = arr1[idx1]
		idx1++
		idx_dst++
	}

	for idx2 < len(arr2) {
		dst[idx_dst] = arr2[idx2]
		idx2++
		idx_dst++
	}
}

func parallelMerge(arr1 []string, arr2 []string, dst []string, ch chan int) {
	if len(arr1) < len(arr2) {
		arr1, arr2 = arr2, arr1
	}

	if len(arr1) != 0 {

		if (len(arr1) + len(arr2)) < 8192 {
			sequentialMerge(arr1, arr2, dst)
		} else {
			xpos1 := len(arr1) / 2
			xpos2 := sort.SearchStrings(arr2, arr1[xpos1])
			xpos_dst := xpos1 + xpos2

			dst[xpos_dst] = arr1[xpos1]

			ch1 := make(chan int)

			go parallelMerge(arr1[:xpos1], arr2[:xpos2], dst[:xpos_dst], ch1)
			go parallelMerge(arr1[xpos1+1:], arr2[xpos2:], dst[xpos_dst+1:], ch1)

			<-ch1
			<-ch1
		}
	}

	if ch != nil {
		ch <- 1
	}
}

func parallelSort(src []string, dst []string, srcToDest bool, ch chan int) {
	if len(src) > 0 {
		if len(src) < 1024 {
			sort.Strings(src)

			if srcToDest {
				for idx, str := range src {
					dst[idx] = str
				}
			}
		} else {
			middle := len(src) / 2

			ch1 := make(chan int)

			go parallelSort(src[:middle], dst[:middle], !srcToDest, ch1)
			go parallelSort(src[middle:], dst[middle:], !srcToDest, ch1)

			<-ch1
			<-ch1

			if srcToDest {
				parallelMerge(src[:middle], src[middle:], dst, nil)
			} else {
				parallelMerge(dst[:middle], dst[middle:], src, nil)
			}
		}
	}

	if ch != nil {
		ch <- 1
	}
}
