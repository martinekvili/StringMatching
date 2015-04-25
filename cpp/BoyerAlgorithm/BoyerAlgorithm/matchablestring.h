#ifndef MATCHABLESTRING_H_INCLUDED
#define MATCHABLESTRING_H_INCLUDED

#include <list>
#include "pattern.h"

class MatchAbleString {
    char *str;
    size_t length;

    MatchAbleString(const MatchAbleString&);
    MatchAbleString& operator=(const MatchAbleString&);

    int match(Pattern &p, const char *str, size_t length);

public:
    MatchAbleString(const char *c);
    ~MatchAbleString();

    std::list<int> match(Pattern &p);
};

#endif // MATCHABLESTRING_H_INCLUDED
