#include "inch.h"
#include "centimeter.h"

Centimeter GetDistance(int a_x, int a_y) {
    return Centimeter(a_x*a_y);
}

int main() {

    Inch inch;
    Centimeter cntmtr;

    int x = 3, y = 5;

    inch = GetDistance(x, y);
    cntmtr = GetDistance(x, y);

    std::cout << "" << inch.GetVal() << std::endl;
    std::cout << "" << cntmtr.GetVal() << std::endl;

    return 0;
}