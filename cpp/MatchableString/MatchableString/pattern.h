#ifndef PATTERN_H
#define PATTERN_H

#include <cctype>
#include <cstring>
#include <string>

class Pattern {
    unsigned int delta1[256];
    int *delta2;

    char *str;
    int length;

    void fillDelta1();

    int rpr(int i);
    void fillDelta2();

	bool preprocessed;

public:

	/**
	 * Creates a pattern object.
	 * @param str The string to use as a pattern
	 */
    Pattern(const std::string& s);
    ~Pattern();

	Pattern(const Pattern&) = delete;
	Pattern& operator=(const Pattern&) = delete;

	const char* getString() const {
		return str;
	}

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

	bool isPreprocessed() const {
		return preprocessed;
	}

	/**
	 * Preprocesses the pattern. Doesn't have to be called by the user.
	 */
    void preprocess();
};

#endif // PATTERN_H
