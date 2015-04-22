#ifndef MATCHABLESTRING_H_INCLUDED
#define MATCHABLESTRING_H_INCLUDED

#include "pattern.h"

class MatchAbleString {
    char *str;
    size_t length;

    MatchAbleString(const MatchAbleString&);
    MatchAbleString& operator=(const MatchAbleString&);

public:
    MatchAbleString(const char *c);
    ~MatchAbleString();

    int match(Pattern &p);
};

#endif // MATCHABLESTRING_H_INCLUDED
