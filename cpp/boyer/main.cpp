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

    Pattern p("Y HA");
    const char *c = "WHICH FINALLY HALTS.  AT THAT POINT";
    MatchAbleString s(c);

    int m = s.match(p);
    std::cout << m << " : '" << c + m << "'" ;

    return 0;
}
