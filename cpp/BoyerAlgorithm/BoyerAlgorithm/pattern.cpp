#include "pattern.h"

void Pattern::fillDelta1() {
    for (int i = 0; i < 256; i++) {
        delta1[i] = (int) str.length();
    }

    for (int i = (int) str.length() - 1; i >= 0; i--) {
        if (delta1[(int) str[i]] == (int) str.length()) {
            delta1[(int) str[i]] = i;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (delta1[i] != (int) str.length()) {
            delta1[i] = (int) str.length() - 1 - delta1[i];
        }
    }
}

int Pattern::rpr(int i) {
	int subPatternLength = (int) str.length() - i - 1;
    int j = i - 1;
    for (; j >= -subPatternLength; j--) {
        if (j >= 0) {
            if (str.compare(j, subPatternLength, str, i + 1, subPatternLength) == 0) {
                if (j == 0 || str[j - 1] != str[i]) {
                    break;
                }
            }
        } else {
			if (str.compare(0, subPatternLength + j, str, i + 1 - j, subPatternLength + j) == 0) {
                break;
            }
        }
    }
    return j;
}

void Pattern::fillDelta2() {
    delta2[(int) str.length() - 1] = 1;
    for (int i = (int) str.length() - 2; i >= 0; i--) {
        delta2[i] = (int) str.length() - rpr(i);
    }
}

void Pattern::preprocess() {
    fillDelta1();
    fillDelta2();
}
