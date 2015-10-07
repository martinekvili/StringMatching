package main

import (
    "fmt"
    "container/list"
    "time"
    "runtime"
    "io/ioutil"
    "os"
    "strconv"
)

type Pattern struct {
    str string
    length int
    delta1 []int
    delta2 []int
}

func (p *Pattern) SetString(s string) {
    p.str = s
    p.length = len(s)
    
    p.delta1 = make([]int, 256)
    p.delta2 = make([]int, p.length)
}

func (p *Pattern) setDelta1() { 
    for i := 0; i < 256; i++ {
        p.delta1[i] = p.length
    }
    
    for i := p.length - 1; i >= 0; i-- {
        p.delta1[p.str[i]] = i
    }
    
    for i := 0; i < 256; i++ {
        if p.delta1[i] != p.length {
            p.delta1[i] = p.length - 1 - p.delta1[i]
        }
    }
}

func (p *Pattern) rpr(i int) int {
    subPattern := p.str[i + 1 :]
    subPatternLength := len(subPattern)
    j := i - 1
    for ; j >= -subPatternLength; j-- {
        if (j >= 0) {
            if (p.str[j : j + subPatternLength] == subPattern) {
                if (j == 0 || p.str[j - 1] != p.str[i]) {
                    break;
                }
            }
        } else {
            if (p.str[: subPatternLength + j] == subPattern[-j :]) {
                break;
            }
        }
    }
    return j;
}

func (p *Pattern) setDelta2() {
    p.delta2[p.length - 1] = 1
    for i := p.length - 2; i >= 0; i-- {
        p.delta2[i] = p.length - p.rpr(i)
    }
}

func (p *Pattern) Preprocess() {
    p.setDelta1()
    p.setDelta2()
}

func findFirst(str string, pat *Pattern) int {
    i := pat.length - 1
    strlen := len(str)
    
    for i < strlen {
        j := pat.length - 1
        for ; j >= 0; j-- {
            if (str[i] != pat.str[j]) {
                break;
            }
            i--
        }
        if (j < 0) {
            return i + 1
        } else {
            if (pat.delta1[str[i]] > pat.delta2[j]) {
                i += pat.delta1[str[i]]
            } else {
                i += pat.delta2[j]
            }
        }
    }
    
    return -1
}

func matchSubstr(str string, pat *Pattern, startPos int) (occurrences list.List) {
    occ := 0
    next := findFirst(str[occ :], pat)
    
    for next != -1 {
        occ += next
        occurrences.PushBack(occ + startPos)
        occ++
        next = findFirst(str[occ :], pat)
    }
    
    return
}

func matchSubstr_(str string, pat *Pattern, strlen int, i int,
                    parts int, occurrencesArray []list.List, ch chan int) {
    var subStr string
    if (i < parts - 1) {
        subStr = str[i * strlen / parts : (i + 1) * strlen / parts + pat.length - 1]
    } else {
        subStr = str[i * strlen / parts :]
    }
    occurrencesArray[i] = matchSubstr(subStr, pat, i * strlen / parts)
    ch <- occurrencesArray[i].Len()
}

func Match (str string, pat *Pattern, parallel bool) []int {
    parts := 8
    strlen := len(str)
    
    size := 0
    occurrencesArray := make([]list.List, parts)
    
    if (!parallel) {
        for i := 0; i < parts; i++ {
            var subStr string
            if (i < parts - 1) {
                subStr = str[i * strlen / parts : (i + 1) * strlen / parts + pat.length - 1]
            } else {
                subStr = str[i * strlen / parts :]
            }
            occurrencesArray[i] = matchSubstr(subStr, pat, i * strlen / parts)
            size += occurrencesArray[i].Len()
        }
    } else {
        ch := make(chan int)
        
        for i := 0; i < parts; i++ {
            go matchSubstr_(str, pat, strlen, i, parts, occurrencesArray, ch)
        }
        
        for i := 0; i < parts; i++ {
            size += <- ch
        }
    }
      
    occurrences := make([]int, size)
    j := 0
    for i := 0; i < parts; i++ {
        for e := occurrencesArray[i].Front(); e != nil; e = e.Next() {
            occurrences[j] = e.Value.(int)
            j++
        }
    }
    
    return occurrences
}

func Measure(str string, pattern string, parallel bool, num int) int {	
	start := time.Now()		// mérés kezdete

	for db := 0; db < 5 * num; db++ {
		var pat Pattern
        pat.SetString(pattern)
		
        pat.Preprocess()
		/*occ = */Match(str, &pat, parallel)
	}
	
	took := time.Since(start).Nanoseconds() / 1000000	// mérés vége
	
    /*if (parallel) {
        fmt.Print("Parallel ")
    } else {
        fmt.Print("Single-thread ")
    }
    fmt.Printf("algorithm took %v ms, and found %v matches\n", took, len(occ))*/
	return int(took) / 5;
}

func main() {
    runtime.GOMAXPROCS(runtime.NumCPU())
    
    bytes, err := ioutil.ReadFile("..\\resources\\" + os.Args[1])
	
	if (err != nil) {
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
	
	for i := 0; i < multiplier - 1; i++ {
		original += string(bytes)
	}
	
	fmt.Printf("%v;", len(original))
              
    fmt.Printf("%v;", Measure(original, os.Args[2], false, num))
    fmt.Printf("%v\n", Measure(original, os.Args[2], true, num))
}