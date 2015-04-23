#include <iostream>

#include "matchablestring.h"

int main()
{
    /*Pattern p("ABYXCDEYX");
    for (int c = 0; c < 256; c++) {
        if (p.getDelta1(c) != p.getLength()) {
            std::cout << (char)c << " (" << c << ") : " << p.getDelta1(c) << std::endl;
        }
    }
    std::cout << std::endl;
    for (size_t i = 0; i < p.getLength(); i++) {
        std::cout << p.getDelta2(i) << ' ';
    }
    std::cout << std::endl;*/

    Pattern p("AT");
    const char *c = "WHICH FINALLY HALTS.  AT THAT POINT";
    MatchAbleString s(c);

    std::list<int> m = s.match(p);
    for (typename std::list<int>::iterator p = m.begin(); p != m.end(); p++) {
        std::cout << *p << " : '" << c + *p << "'" << std::endl;
    }

    return 0;
}
