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

var cache [][]int

func getRandArray() {
	for i := range cache[1] {
		cache[1][i] = rand.Intn(1000)
	}
}

/*func printArray(arr []int) {
	for _, i := range arr {
		fmt.Printf("%v ", i)
	}
	fmt.Print("\n")
}*/

func parallelSort(num int, depth int, ch chan int) {
	if (depth == 0) {
		sort.Ints(cache[num])
		ch <- 1
		return
	} else {
		copy(cache[2 * num], cache[num][:len(cache[num])/2])
		copy(cache[2 * num + 1], cache[num][len(cache[num])/2:])
		
		ch1 := make(chan int)
		
		go parallelSort(2 * num, depth - 1, ch1)
		go parallelSort(2 * num + 1, depth - 1, ch1)
		
		<- ch1
		<- ch1
		
		var i, j, k int
		for i < len(cache[2 * num]) || j < len(cache[2 * num + 1]) {
			switch {
			case i == len(cache[2 * num]):
				cache[num][k] = cache[2 * num + 1][j]
				j++
			case j == len(cache[2 * num + 1]):
				cache[num][k] = cache[2 * num][i]
				i++
			case cache[2 * num][i] < cache[2 * num + 1][j]:
				cache[num][k] = cache[2 * num][i]
				i++
			default:
				cache[num][k] = cache[2 * num + 1][j]
				j++
			}
			k++
		}
		
		if ch != nil {
			ch <- 1
		}
	}
}

func sortArray(depth int) {
	if depth == 0 {
		sort.Ints(cache[1])
	} else {
		parallelSort(1, depth, nil)
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
		getRandArray()
		
		if verbose {
			fmt.Printf("Measurement number %v...", i)
		}
	
		start := time.Now()
		sortArray(depth)
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

func initialize (size int) {
	rand.Seed(time.Now().UnixNano())
	runtime.GOMAXPROCS(runtime.NumCPU())
	
	cache = make([][]int, 128)
	for i := 0; i < 7; i++ {
		tmp := int(math.Pow(2, float64(i)))
		for j := 0; j < tmp; j++ {
			cache[tmp + j] = make([]int, size / tmp)
		}
	}
}

func main() {
	args := os.Args[1:]
	size, err := strconv.Atoi(args[0])
	if err != nil {
		return
	}
	verbose := len(args) > 1 && args[1] == "-v"
	
	initialize(size)
	
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