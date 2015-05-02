package main

import (
    "fmt"
    "container/list"
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
    
    p.delta1 = make([]int, 128)
    p.delta2 = make([]int, p.length)
}

func (p *Pattern) setDelta1() { 
    for i := 0; i < 128; i++ {
        p.delta1[i] = p.length
    }
    
    for i := p.length - 1; i >= 0; i-- {
        p.delta1[p.str[i]] = i
    }
    
    for i := 0; i < 128; i++ {
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
   // fmt.Println(startPos)
    occ := 0
    next := findFirst(str[occ :], pat)
    
    for next != -1 {
        occ += next
        //fmt.Println(occ + startPos)
        occurrences.PushBack(occ + startPos)
        occ++
        next = findFirst(str[occ :], pat)
    }
    
    return
}

func Match (str string, pat *Pattern) []int {
    parts := 8
    strlen := len(str)
    
    size := 0
    occurrencesArray := make([]list.List, parts)
    
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

func main() {
    var pat Pattern
    pat.SetString("ence")
    
    pat.Preprocess()
    
    /*for i := 0; i < 128; i++ {
        c := rune(i)
        fmt.Printf("%v: %v\n", c, pat.delta1[i])
    }*/
    
    /*for i := 0; i < pat.length; i++ {
        fmt.Printf("%v ", pat.delta2[i])
    }
    fmt.Println()*/
    
    str := "i had to, hence, i peed the fence. i don't see the adHence"
    
    /*l := matchSubstr(str, &pat)
    for e := l.Front(); e != nil; e = e.Next() {
    found := e.Value.(int)
		fmt.Printf("%v: %s\n", found, str[found : found + pat.length])
	}*/
    
    for _, found := range Match(str, &pat) {
        fmt.Printf("%v: %s\n", found, str[found : found + pat.length])
    }
    
    //found := FindFirst(str, &pat)
    //fmt.Println(str[found : found + pat.length])
}