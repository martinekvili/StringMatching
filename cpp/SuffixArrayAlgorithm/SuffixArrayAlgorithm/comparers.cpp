#include "comparers.h"

int ComparerBase::compare(int num) const {
	int comp = strncmp(str + substringArray[num], pattern, patternLength);
	if (comp != 0) {
		return comp;
	}
	else {
		return checkIfValid(num);
	}
}

int FirstOccurenceComparer::checkIfValid(int num) const {
	if (num == 0 || strncmp(str + substringArray[num - 1], pattern, patternLength) != 0) {
		return 0;
	}
	else {
		return 1;
	}
}

int LastOccurenceComparer::checkIfValid(int num) const {
	if (num == length - 1 || strncmp(str + substringArray[num + 1], pattern, patternLength) != 0) {
		return 0;
	}
	else {
		return -1;
	}
}