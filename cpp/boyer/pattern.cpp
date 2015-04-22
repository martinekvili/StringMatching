#include "pattern.h"

void Pattern::setDelta1(int c, unsigned int val) {
    delta1[c] = val;
}

unsigned int Pattern::getDelta1(int c) {
    return delta1[c];
}

int Pattern::getDelta2(int i) {
    return delta2[i];
}

char Pattern::operator[] (int i) {
    return str[i];
}

void Pattern::fillDelta1() {
    for (int i = 0; i < 256; i++) {
        delta1[i] = length;
    }

    for (int i = (int) length - 1; i >= 0; i--) {
        if (delta1[(int) str[i]] == length) {
            delta1[(int) str[i]] = i;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (delta1[i] != length) {
            delta1[i] = length - 1 - delta1[i];
        }
    }
}

int Pattern::rpr(int i) {
    int subPatternLength = strlen(str + i + 1);
    int j = i - 1;
    for (; j >= -subPatternLength; j--) {
        if (j >= 0) {
            if (strncmp(str + j, str + i + 1, subPatternLength) == 0) {
                if (j == 0 || str[j - 1] != str[i]) {
                    break;
                }
            }
        } else {
            if (strncmp(str, str + i + 1 - j, subPatternLength + j) == 0) {
                break;
            }
        }
    }
    return j;
}

void Pattern::fillDelta2() {
    delta2[length - 1] = 1;
    for (int i = length - 2; i >= 0; i--) {
        delta2[i] = length - rpr(i);
    }
}

void Pattern::preprocess() {
    fillDelta1();
    fillDelta2();
}

Pattern::Pattern(const char *c) {
    length = strlen(c);
    str = new char[length + 1];
    strcpy(str, c);

    delta2 = new int[length];

    preprocess();
}

Pattern::~Pattern() {
    delete[] delta2;
    delete[] str;
}
