#include "matchablestring.h"

MatchAbleString::MatchAbleString(const char *c) {
    length = strlen(c);
    str = new char[length + 1];
    strcpy(str, c);
}

MatchAbleString::~MatchAbleString() {
    delete[] str;
}

int MatchAbleString::match(Pattern &p) {
    size_t i = p.getLength() - 1;
    while (i < length) {
        int j = p.getLength() - 1;
        for (; j >= 0; j--, i--) {
            if (str[i] != p[j]) {
                break;
            }
        }
        if (j < 0) {
            return i + 1;
        } else {
            int delta1 = p.getDelta1(str[i]);
            int delta2 = p.getDelta2(j);
            i += delta1 > delta2 ? delta1 : delta2;
        }
    }
    return -1;
}
