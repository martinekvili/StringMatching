#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#include <cctype>
#include <cstring>

class Pattern {
    unsigned int delta1[256];
    int *delta2;

    char *str;
    int length;

    void fillDelta1();

    int rpr(int i);
    void fillDelta2();

public:
    Pattern(const char *c);
    ~Pattern();

	Pattern(const Pattern&) = delete;
	Pattern& operator=(const Pattern&) = delete;

    int getLength() const {
        return length;
    }

	unsigned int Pattern::getDelta1(int c) const {
		return delta1[c];
	}

	int Pattern::getDelta2(int i) const {
		return delta2[i];
	}

	char Pattern::operator[] (int i) const {
		return str[i];
	}

    void preprocess();
};

#endif // PATTERN_H_INCLUDED
