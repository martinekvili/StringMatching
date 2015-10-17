package main

import "sort"

type MatchAbleString struct {
	str            string
	length         int
	substringArray []string
	isPreProcessed bool
}

func (s *MatchAbleString) SetString(str string) {
	s.str = str
	s.length = len(str)

	s.substringArray = make([]string, s.length)
	for i := 0; i < s.length; i++ {
		s.substringArray[i] = str[i:]
	}

	s.isPreProcessed = false
}

func (s *MatchAbleString) PreProcess(parallel bool) {
	if !parallel {
		sort.Strings(s.substringArray)
	} else {
		acc := make([]string, s.length)

		parallelSort(s.substringArray, acc, false, nil)
	}

	s.isPreProcessed = true
}

func binarySearch(min int, max int, substringArray []string, pattern string, comparer func(int, []string, string) int) int {
	if min == max {
		return -1
	}

	var num int
	num = (min + max) / 2

	switch comparer(num, substringArray, pattern) {
	case 0:
		return num
	case -1:
		return binarySearch(num+1, max, substringArray, pattern, comparer)
	case 1:
		return binarySearch(min, num, substringArray, pattern, comparer)
	default:
		// No way we ever get here.
		panic("Unhandled error.")
	}
}

func (s *MatchAbleString) Match(pattern string) []int {
	if !s.isPreProcessed {
		panic("This MatchAbleString hasn't been preprocessed yet!")
	}

	first := binarySearch(0, s.length, s.substringArray, pattern, firstOccurrenceComparer)
	last := binarySearch(0, s.length, s.substringArray, pattern, lastOccurrenceComparer)

	if first == -1 {
		return make([]int, 0)
	} else {
		arr := make([]int, last-first+1)
		for i := range arr {
			arr[i] = s.length - len(s.substringArray[first+i])
		}

		sort.Ints(arr)

		return arr
	}
}
