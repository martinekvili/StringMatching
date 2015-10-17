package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"runtime"
	"strconv"
	"time"
)

func Measure(str string, pattern string, parallel bool, num int) int {
	start := time.Now() // mérés kezdete

	for db := 0; db < 5*num; db++ {
		var pat Pattern
		pat.SetString(pattern)

		pat.Preprocess()
		/*occ = */ Match(str, &pat, parallel)
	}

	took := time.Since(start).Nanoseconds() / 1000000 // mérés vége

	/*if (parallel) {
	      fmt.Print("Parallel ")
	  } else {
	      fmt.Print("Single-thread ")
	  }
	  fmt.Printf("algorithm took %v ms, and found %v matches\n", took, len(occ))*/
	return int(took) / 5
}

func MeasureSimple() {
	str := "i had to, Hence, i peed the fence. i don't see the adHence"

	var pat Pattern
	pat.SetString("ence")
	pat.Preprocess()

	occs := Match(str, &pat, true)

	for _, occ := range occs {
		fmt.Printf("%v : %v\n", occ, str[occ:occ+pat.length])
	}
}

func MeasureReadFile() {
	bytes, err := ioutil.ReadFile("..\\resources\\" + os.Args[1])

	if err != nil {
		fmt.Print("No such file")
		return
	}

	multiplier, err2 := strconv.Atoi(os.Args[3])
	if err2 != nil {
		fmt.Print("Bad number")
		return
	}

	num, err3 := strconv.Atoi(os.Args[4])
	if err3 != nil {
		fmt.Print("Bad number")
		return
	}

	original := string(bytes)

	for i := 0; i < multiplier-1; i++ {
		original += string(bytes)
	}

	fmt.Printf("%v;", len(original))

	fmt.Printf("%v;", Measure(original, os.Args[2], false, num))
	fmt.Printf("%v\n", Measure(original, os.Args[2], true, num))
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	//MeasureSimple()

	MeasureReadFile()
}
