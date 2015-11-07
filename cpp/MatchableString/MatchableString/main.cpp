#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "matchablestrings.h"
#include "pattern.h"

using CreatorFunction = std::unique_ptr<MatchableString>(*)(const std::string&);

char* ReadAllText(std::string path) {
	std::ifstream t;
	t.open(path, std::ifstream::binary);    // open input file
	t.seekg(0, t.end);						// go to the end
	int length = (int)t.tellg();			// report location (this is the length)
	t.seekg(0, t.beg);						// go back to the beginning
	char *orig = new char[length + 1];		// allocate memory for a buffer of appropriate dimension
	t.read(orig, length);					// read the whole file into the buffer
	orig[length] = '\0';
	t.close();								// close file handle

	return orig;
}
    
void measureSimple(CreatorFunction func) {
	std::string  orig = "i had to, Hence, i peed the fence. i don't see the adHence";
	std::unique_ptr<MatchableString> sm = func(orig);
	sm->preprocess(false);

	std::string pat = "ence";
	Pattern p(pat);
	std::vector<int> h = sm->match(p, false);

	for (auto i : h) {
		std::cout << i << " : " << orig.substr(i, pat.length()) << std::endl;
	}

	char c;
	std::cin >> c;
}

int main(int argc, char **argv)
{
	measureSimple(MatchableStrings::createBoyer);
	measureSimple(MatchableStrings::createSuffixArray);

	return 0;
}