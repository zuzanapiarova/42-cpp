#include "Fixed.hpp"
#include "Point.hpp"

bool bsp(const Point& a, const Point& b, const Point& c, const Point& p);

int main(void)
{
    Point a(1,1);
    Point b(5,1);
    Point c(3, 3);

    std::cout << std::endl;
    Point p0(3,2);
    // Point p1(0,0);
    // Point p2(2,1);
    // Point p3(1,1);
    // Point p4(4.7, 1.1);
    // Point p5(0.00390625,0.00390625);
    std::cout << std::endl;

    std::cout << "This point is inside: " << bsp(a, b, c, p0) << std::endl;
    // std::cout << "This point is outside: " << bsp(a, b, c, p1) << std::endl;
    // std::cout << "This point is on border: " << bsp(a, b, c, p2) << std::endl;
    // std::cout << "This point is right in corner: " << bsp(a, b, c, p3) << std::endl;
    // std::cout << "This point is inside very close to corner: " << bsp(a, b, c, p4) << std::endl;
    // std::cout << "This point is outside very close to corner: " << bsp(a, b, c, p5) << std::endl;

    return 0;
}
