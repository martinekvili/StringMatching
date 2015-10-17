package main

func stringCompare(one, other string) int {
	if len(one) >= len(other) {
		start := one[:len(other)]

		if start == other {
			return 0
		} else if start < other {
			return -1
		} else {
			return 1
		}
	} else {
		start := other[:len(one)]

		if one <= start {
			return -1
		} else {
			return 1
		}
	}
}

func firstOccurrenceComparer(num int, substringArray []string, pattern string) int {
	ret := stringCompare(substringArray[num], pattern)

	if ret != 0 {
		return ret
	} else {
		if num == 0 || stringCompare(substringArray[num-1], pattern) != 0 {
			return 0
		} else {
			return 1
		}
	}
}

func lastOccurrenceComparer(num int, substringArray []string, pattern string) int {
	ret := stringCompare(substringArray[num], pattern)

	if ret != 0 {
		return ret
	} else {
		if num == len(substringArray)-1 || stringCompare(substringArray[num+1], pattern) != 0 {
			return 0
		} else {
			return -1
		}
	}
}
