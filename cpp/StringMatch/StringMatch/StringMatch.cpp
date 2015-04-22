#include "StringMatch.h"

StringMatch::StringMatch(const char *orig) {
	length = strlen(orig);

	original = new char[length + 1];
	strcpy(original, orig);

	substringArray = new char*[length];
	int i = 0;
	for (char *o = original; *o != '\0'; o++, i++)
	{
		substringArray[i] = o;
	}
}

StringMatch::~StringMatch() {
	delete[] original;
	delete[] substringArray;
}

void StringMatch::preprocess(bool parallel) {
	StringSorter::sort(substringArray, length, parallel ? 3 : 0);
}

int StringMatch::binarySearch(int min, int max, const char *pattern, const ComparerBase *comparer) const {
	if (min == max) {
		return -1;
	}

	int num = (min + max) / 2;

	switch (comparer->compare(num)) {
	case 0:
		return num;
	case -1:
		return binarySearch(num + 1, max, pattern, comparer);
	case 1:
		return binarySearch(min, num, pattern, comparer);
	}
}

std::vector<char*> StringMatch::match(const char *pattern) const {
	ComparerBase *foc = new FirstOccurenceComparer(pattern, substringArray, length);
	ComparerBase *loc = new LastOccurenceComparer(pattern, substringArray, length);

	int first = binarySearch(0, length, pattern, foc);
	int last = binarySearch(0, length, pattern, loc);


	delete foc;
	delete loc;

	if (first == -1)
	{
		return std::vector<char*>();
	}
	else
	{
		return std::vector<char*>(substringArray + first, substringArray + last + 1);
	}
}

//void StringMatch::print() const {
//	for (size_t i = 0; i < length; i++) {
//		std::cout << substringArray[i] << std::endl;
//	}
//}