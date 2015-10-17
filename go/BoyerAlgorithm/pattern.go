package main

type Pattern struct {
	str    string
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
	subPattern := p.str[i+1:]
	subPatternLength := len(subPattern)
	j := i - 1
	for ; j >= -subPatternLength; j-- {
		if j >= 0 {
			if p.str[j:j+subPatternLength] == subPattern {
				if j == 0 || p.str[j-1] != p.str[i] {
					break
				}
			}
		} else {
			if p.str[:subPatternLength+j] == subPattern[-j:] {
				break
			}
		}
	}
	return j
}

func (p *Pattern) setDelta2() {
	p.delta2[p.length-1] = 1
	for i := p.length - 2; i >= 0; i-- {
		p.delta2[i] = p.length - p.rpr(i)
	}
}

func (p *Pattern) Preprocess() {
	p.setDelta1()
	p.setDelta2()
}
