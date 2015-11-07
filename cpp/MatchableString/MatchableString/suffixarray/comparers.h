#ifndef COMPARERS_H
#define COMPARERS_H

#include <cstring>

class ComparerBase
{
private:
	virtual int checkIfValid(int num) const = 0;

protected:
	const char *str;
	const char *pattern;
	int * const substringArray;
	size_t length;
	size_t patternLength;

public:
	ComparerBase(const char *s, const char *p, int* const ssA, size_t l) : 
			str(s),  pattern(p), substringArray(ssA), length(l), patternLength(strlen(pattern)) {}

	int compare(int num) const;

	virtual ~ComparerBase() {}
};

class FirstOccurenceComparer : public ComparerBase
{
private:
	int checkIfValid(int num) const override;

public:
	FirstOccurenceComparer(const char *s, const char *p, int* const ssA, size_t l) : ComparerBase(s, p, ssA, l) {}
};

class LastOccurenceComparer : public ComparerBase
{
private:
	int checkIfValid(int num) const override;

public:
	LastOccurenceComparer(const char *s, const char *p, int* const ssA, size_t l) : ComparerBase(s, p, ssA, l) {}
};

#endif //COMPARERS_H