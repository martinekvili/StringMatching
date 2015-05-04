package main

import (
	"fmt"
	"sort"
	"io/ioutil"
	"time"
	"runtime"
	"os"
)

func parallelSort(arr []string, depth int, ch chan int) {
	if (depth == 0) {
		sort.Strings(arr)
		ch <- 1
		return
	} else {
		firstHalf := make([]string, len(arr) / 2)
		secondHalf := make([]string, len(arr) / 2)
		copy(firstHalf, arr[:len(arr)/2])
		copy(secondHalf, arr[len(arr)/2:])
		
		ch1 := make(chan int)
		
		go parallelSort(firstHalf, depth - 1, ch1)
		go parallelSort(secondHalf, depth - 1, ch1)
		
		<- ch1
		<- ch1
		
		var i, j, k int
		for i < len(firstHalf) || j < len(secondHalf) {
			switch {
			case i == len(firstHalf):
				arr[k] = secondHalf[j]
				j++
			case j == len(secondHalf):
				arr[k] = firstHalf[i]
				i++
			case firstHalf[i] < secondHalf[j]:
				arr[k] = firstHalf[i]
				i++
			default:
				arr[k] = secondHalf[j]
				j++
			}
			k++
		}
		
		if ch != nil {
			ch <- 1
		}
	}
}

func sortArray(arr []string, parallel bool) {
	if !parallel {
		sort.Strings(arr)
	} else {
		parallelSort(arr, 3, nil)
	}
}

func preprocess(substringArray []string, parallel bool) {
	sortArray(substringArray, parallel);
}

func stringCompare(one, other string) int {
	if (len(one) >= len(other)) {
		start := one[:len(other)]
		
		if (start == other) {
			return 0
		} else if (start < other) {
			return -1
		} else {
			return 1
		}
	} else {
		start := other[:len(one)]
		
		if (one <= start) {
			return -1
		} else {
			return 1
		}
	}
}

func firstOccurrenceComparer(num int, substringArray []string, pattern string) int {
	ret := stringCompare(substringArray[num], pattern)
	
	if (ret != 0) {
		return ret
	} else {
		if (num == 0 || stringCompare(substringArray[num - 1], pattern) != 0) {
			return 0
		} else {
			return 1
		}
	}
}

func lastOccurrenceComparer(num int, substringArray []string, pattern string) int {
	ret := stringCompare(substringArray[num], pattern)
	
	if (ret != 0) {
		return ret
	} else {
		if (num == len(substringArray) - 1 || stringCompare(substringArray[num + 1], pattern) != 0) {
			return 0
		} else {
			return -1
		}
	}
}

func binarySearch(min int, max int, substringArray []string, pattern string, comparer func(int, []string, string) int) int {
	if (min == max) {
		return -1
	}

	var num int
	num = (min + max) / 2

	switch (comparer(num, substringArray, pattern)) {
	case 0:
		return num
	case -1:
		return binarySearch(num + 1, max, substringArray, pattern, comparer)
	case 1:
		return binarySearch(min, num, substringArray, pattern, comparer)
	default:
		// No way we ever get here.
		panic("Unhandled error.")
	}	
}

func match(substringArray []string, pattern string) []string {
	first := binarySearch(0, len(substringArray), substringArray, pattern, firstOccurrenceComparer)
	last := binarySearch(0, len(substringArray), substringArray, pattern, lastOccurrenceComparer)
	
	if (first == -1) {
		return make([]string, 0)
	} else {
		arr := make([]string, last - first + 1)
		for i := range arr {
			arr[i] = substringArray[first + i]
		}
		return arr
	}
}

func measure (original string, substringArray []string, parallel bool) int {
	var start time.Time
	var took int64

	for db := 0; db < 5; db++ {
		for i := 0; i < len(original); i++ {
			substringArray[i] = original[i:]
		}
		
		start = time.Now()
		preprocess(substringArray, parallel)
		took += time.Since(start).Nanoseconds() / 1000000
	}
	
	return int(took / 5);
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	//original := "CGATATATCGG"
	bytes, err := ioutil.ReadFile("..\\..\\resources\\" + os.Args[1])
	
	if (err != nil) {
		fmt.Print("No such file")
		return
	}
	
	original := string(bytes)
	
	for i := 0; i < 7; i++ {
		original += string(bytes)
	}
	
	fmt.Printf("%v;", len(original))
	
	substringArray := make([]string, len(original))
	
	
	took := measure(original, substringArray, false)
	fmt.Printf("%v;", took)
	took = measure(original, substringArray, true)
	fmt.Printf("%v\n", took)
	
	/*
	start = time.Now()
	matches := match(substringArray, "expostulate")
	took = time.Since(start).Nanoseconds() / 1000000
	
	fmt.Printf("Matching took %v s %v ms\n\n", took / 1000, took % 1000)
	*/
	
	/*
	if(len(matches) == 0) {
		fmt.Print("No matches found\n")
	} else {
		fmt.Printf("%v matches found\n", len(matches))
		
		for _, s := range matches {
			fmt.Print(s[:len("expostulate")])
			fmt.Print("\n")
		}
	}
	*/
	
}