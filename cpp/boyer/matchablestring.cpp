#include "matchablestring.h"

MatchAbleString::MatchAbleString(const char *c) {
    length = strlen(c);
    str = new char[length + 1];
    strcpy(str, c);
}

MatchAbleString::~MatchAbleString() {
    delete[] str;
}

int MatchAbleString::match(Pattern &p, const char *str_, size_t length_) {
    size_t i = p.getLength() - 1;
    while (i < length_) {
        int j = p.getLength() - 1;
        for (; j >= 0; j--, i--) {
            if (str_[i] != p[j]) {
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

std::list<int> MatchAbleString::match(Pattern &p) {
    std::list<int> occurrences;
    int occ = 0, next;
    while ((next = match(p, str + occ, length - occ)) != -1) {
        occ += next;
        occurrences.push_back(occ);
        occ++;
    }
    return occurrences;
}
