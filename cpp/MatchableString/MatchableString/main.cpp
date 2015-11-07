#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <Windows.h>

#include "matchablestrings.h"
#include "pattern.h"

using CreatorFunction = std::unique_ptr<MatchableString>(*)(const char*);

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

int measure(const char *orig, const char *pat, bool parallel, int matchNum, CreatorFunction func) {
	std::vector<int> l;

	long int start = GetTickCount();	// mérés indul 

	for (int i = 0; i < 5; i++) {
		auto str = func(orig);
		str->preprocess(parallel);

		for (int j = 0; j < matchNum; j++) {
			Pattern p(pat);
			l = str->match(p, parallel);
		}
	}

	int elapsed = GetTickCount() - start;	// mérés vége

	/*std::cout << (parallel ? "Parallel" : "Single thread") << " matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
	std::cout << "Found " << l.size() << " matches." << std::endl;*/

	return elapsed / 5;
}

void measureReadFile(char **argv) {
	std::string path = "..\\resources\\";
	path += argv[2];

	CreatorFunction func = strcmp(argv[1], "boyer") == 0 ? MatchableStrings::createBoyer : MatchableStrings::createSuffixArray;
	int multiplier = atoi(argv[4]);
	int matchNum = atoi(argv[5]);

	const char *orig = ReadAllText(path);
	size_t length = strlen(orig);

	size_t tmp = (length + 1) * multiplier + 1;
	char *str = new char[tmp];
	str[0] = '\0';
	for (int i = 0; i < multiplier; i++) {
		strcat_s(str, tmp, orig);
	}

	delete[] orig;

	std::cout << strlen(str) << ";";

	std::cout << measure(str, argv[3], false, matchNum, func) << ";";
	std::cout << measure(str, argv[3], true, matchNum, func) << std::endl;
}
    
void measureSimple(CreatorFunction func) {
	std::string  orig = "i had to, Hence, i peed the fence. i don't see the adHence";
	std::unique_ptr<MatchableString> sm = func(orig.data());
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
	/*measureSimple(MatchableStrings::createBoyer);
	measureSimple(MatchableStrings::createSuffixArray);*/

	measureReadFile(argv);

	return 0;
}