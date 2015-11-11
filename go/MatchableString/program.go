package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"runtime"
	"strconv"
	"time"
)

type CreatorFunction func(string) MatchableString

func Measure(str string, pattern string, parallel bool, num int, creator CreatorFunction) int {
	start := time.Now() // mérés kezdete
	//var occ []int

	for db := 0; db < 5; db++ {
		matchable := creator(str)
		matchable.Preprocess(parallel)

		var pat Pattern
		pat.SetString(pattern)

		for m := 0; m < num; m++ {
			/*occ = */ matchable.Match(&pat, parallel)
		}
	}

	took := time.Since(start).Nanoseconds() / 1000000 // mérés vége

	/*if parallel {
		fmt.Print("Parallel ")
	} else {
		fmt.Print("Single-thread ")
	}
	fmt.Printf("algorithm took %v ms, and found %v matches\n", took, len(occ))*/

	return int(took) / 5
}

func MeasureReadFile() {
	bytes, err := ioutil.ReadFile("..\\resources\\" + os.Args[2])

	if err != nil {
		fmt.Print("No such file")
		return
	}

	multiplier, err2 := strconv.Atoi(os.Args[4])
	if err2 != nil {
		fmt.Print("Bad number")
		return
	}

	num, err3 := strconv.Atoi(os.Args[5])
	if err3 != nil {
		fmt.Print("Bad number")
		return
	}

	original := string(bytes)

	for i := 0; i < multiplier-1; i++ {
		original += string(bytes)
	}

	fmt.Printf("%v;", len(original))

	if os.Args[1] == "both" {
		fmt.Printf("%v;", num)

		fmt.Printf("%v;", Measure(original, os.Args[3], true, num, createBoyer))
		fmt.Printf("%v\n", Measure(original, os.Args[3], true, num, createSuffixArray))
	} else {
		var creator CreatorFunction
		if os.Args[1] == "boyer" {
			creator = createBoyer
		} else {
			creator = createSuffixArray
		}

		fmt.Printf("%v;", Measure(original, os.Args[3], false, num, creator))
		fmt.Printf("%v\n", Measure(original, os.Args[3], true, num, creator))
	}

}

func measureSimple(creator CreatorFunction) {
	str := "i had to, Hence, i peed the fence. i don't see the adHence"

	matchable := creator(str)
	matchable.Preprocess(true)

	var pat Pattern
	pat.SetString("ence")
	pat.Preprocess()

	occs := matchable.Match(&pat, true)

	for _, occ := range occs {
		fmt.Printf("%v : %v\n", occ, str[occ:occ+pat.length])
	}
}

func createBoyer(str string) MatchableString {
	var boyer MatchableStringB
	boyer.SetString(str)

	return &boyer
}

func createSuffixArray(str string) MatchableString {
	var suffixarray MatchableStringSA
	suffixarray.SetString(str)

	return &suffixarray
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	//measureSimple(createBoyer)
	//measureSimple(createSuffixArray)

	MeasureReadFile()
}
