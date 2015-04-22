package main

import (
	"fmt"
	"math/rand"
	"math"
	"sort"
	"time"
	"runtime"
	"os"
	"strconv"
)

func getRandArray(size int) []int {
	arr := make([]int, size)
	for i := range arr {
		arr[i] = rand.Intn(1000)
	}
	return arr
}

/*func printArray(arr []int) {
	for _, i := range arr {
		fmt.Printf("%v ", i)
	}
	fmt.Print("\n")
}*/

func parallelSort(arr []int, depth int, ch chan int) {
	if (depth == 0) {
		sort.Ints(arr)
		ch <- 1
		return
	} else {
		firstHalf := make([]int, len(arr) / 2)
		secondHalf := make([]int, len(arr) / 2)
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

func sortArray(arr []int, depth int) {
	if depth == 0 {
		sort.Ints(arr)
	} else {
		parallelSort(arr, depth, nil)
	}
}

func measurement (size int, depth int, verbose bool) (tim int64) {
	if verbose {
		fmt.Print("Starting measurement ( ")
		if depth == 0 {
			fmt.Print("non - parallel")
		} else {
			fmt.Printf("parallel - %v pieces", math.Pow(2, float64(depth)))
		}
		fmt.Printf(" algorithm, size of the array: %v M )\n\n", size / 1000000)
	}
	
	for i := 0; i < 5; i++ {
		arr := getRandArray(size)
		
		if verbose {
			fmt.Printf("Measurement number %v...", i)
		}
	
		start := time.Now()
		sortArray(arr, depth)
		took := time.Since(start).Nanoseconds() / 1000000
		
		if verbose {
			fmt.Printf("DONE ( %v s, %v ms )\n", took / 1000, took % 1000)
		}
		
		tim += took
	}
	
	tim /= 5
	
	if verbose {
		fmt.Printf("\nSorting took on average %v seconds and %v milliseconds.\n\n", tim / 1000, tim % 1000)
	}
	
	return
}

func main() {
	rand.Seed(time.Now().UnixNano())
	runtime.GOMAXPROCS(runtime.NumCPU())
	
	args := os.Args[1:]
	size, err := strconv.Atoi(args[0])
	if err != nil {
		return
	}
	verbose := len(args) > 1 && args[1] == "-v"
	
	times := make([]int64, 7)
	for i := range times {
		times[i] = measurement(size, i, verbose)
	}
	
	if !verbose {
		fmt.Printf("%v;", size / 1000000)
		for _, tim := range times {
			fmt.Printf("%v;", tim)
		}
		fmt.Print("\n")
	}
}