#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#include <string>
#include <vector>

class Pattern {
	std::string str;

    std::vector<int> delta1;
	std::vector<int> delta2;

    void fillDelta1();

    int rpr(int i);
    void fillDelta2();

public:
	Pattern(std::string s) : str(s), delta1(256), delta2(s.length()) {}

	Pattern(const Pattern&) = delete;
	Pattern& operator=(const Pattern&) = delete;

    int getLength() const {
        return (int) str.length();
    }

	char operator[] (int i) const {
		return str[i];
	}

	int getDelta1(int c) const {
		return delta1[c];
	}

	int getDelta2(int i) const {
		return delta2[i];
	}

    void preprocess();
};

#endif // PATTERN_H_INCLUDED
