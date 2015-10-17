package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"runtime"
	//"strconv"
	"time"
)

func measure(original string, pattern string, parallel bool, num int) int {
	var start time.Time
	var took int64
	//var occs []int

	for db := 0; db < 5; db++ {
		var s MatchAbleString
		s.SetString(original)

		start = time.Now()
		s.PreProcess(parallel)
		took += time.Since(start).Nanoseconds() / 1000000

		for i := 0; i < num; i++ {
			/*occs = */ s.Match(pattern)
		}
	}

	//fmt.Printf("Found %v occurrences.\n", len(occs))

	return int(took / 5)
}

func MeasureReadFile() {
	bytes, err := ioutil.ReadFile("..\\..\\resources\\" + os.Args[1])

	if err != nil {
		fmt.Print("No such file")
		return
	}

	/*num, err2 := strconv.Atoi(os.Args[3])
	if err2 != nil {
		fmt.Print("Bad number")
		return
	}*/

	original := string(bytes)

	fmt.Printf("%v;", len(original))

	//fmt.Printf("%v;", num)

	fmt.Printf("%v;", measure(original, os.Args[2], false, 1))
	fmt.Printf("%v\n", measure(original, os.Args[2], true, 1))
}

func MeasureSimple() {
	str := "i had to, Hence, i peed the fence. i don't see the adHence"
	pat := "ence"

	var s MatchAbleString
	s.SetString(str)
	s.PreProcess(false)

	/*for _, b := range s.substringArray {
		fmt.Printf("%v \n", b)
	}*/

	occs := s.Match(pat)

	for _, occ := range occs {
		fmt.Printf("%v : %v\n", occ, str[occ:occ+len(pat)])
	}
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	MeasureReadFile()

	//MeasureSimple()
}
