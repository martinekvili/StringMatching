#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#include <cctype>
#include <cstring>

class Pattern {
    unsigned int delta1[256];

    int *delta2;

    char *str;
    size_t length;

    Pattern(const Pattern&);
    Pattern& operator=(const Pattern&);

    void setDelta1(int c, unsigned int val);
    void fillDelta1();

    int rpr(int i);
    void fillDelta2();

public:
    Pattern(const char *c);
    ~Pattern();

    size_t getLength() {
        return length;
    }
    char operator[] (int i);

    unsigned int getDelta1(int c);
    int getDelta2(int i);

    void preprocess();
};

#endif // PATTERN_H_INCLUDED