#include "matchablestring.h"

MatchableString::MatchableString(const char *c) {
	length = (int)strlen(c);
	str = new char[length + 1];
	strcpy_s(str, length + 1, c);
}

MatchableString::~MatchableString() {
	delete[] str;
}