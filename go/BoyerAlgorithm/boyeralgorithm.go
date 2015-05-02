package main

import (
    "fmt"
)

type Pattern struct {
    str string
    length int
    delta1 []int
    delta2 []int
}

func (p *Pattern) setString(s string) {
    p.str = s
    p.length = len(s)
}

func (p *Pattern) setDelta1() {
    p.delta1 = make([]int, 128)
    
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

func (p *Pattern) setDelta2() {
    // TODO
}

func (p *Pattern) preprocess() {
    p.setDelta1()
    p.setDelta2()
}

func main() {
    var pat Pattern
    pat.setString("ence")
    
    pat.preprocess()
    
    /*for i := 0; i < 128; i++ {
        c := rune(i)
        fmt.Printf("%v: %v\n", c, pat.delta1[i])
    }*/
    
    
    //pat.setDelta2()
}