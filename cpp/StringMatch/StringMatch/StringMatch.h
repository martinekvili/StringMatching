#ifndef STRINGMATCH_H
#define STRINGMATCH_H

#include <cstring>
#include <algorithm>
//#include <iostream>
#include <vector>

#include "Comparers.h"
#include "StringSorter.h"

class StringMatch
{
private:
	char *original;
	int *substringArray;
	size_t length;

	StringMatch(const StringMatch &);
	StringMatch& operator= (const StringMatch &);

public:
	StringMatch(const char *orig);

	~StringMatch();

	//bool operator() (const char *one, const char *other) const;

	void preprocess(bool parallel = false);

	int binarySearch(int min, int max, const char *pattern, const ComparerBase *comparer) const;

	std::vector<char*> match(const char *pattern) const;
	
	//void print() const;
};

#endif // STRINGMATCH_H