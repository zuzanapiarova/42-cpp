#include "Base.hpp"

// tests
// 1. try to cast other class into identify
// 2. test idenfity with pointer with nullptr
int main()
{
    std::srand(static_cast<unsigned int>(std::time(0))); // set the seed of the pseudo-random number generator once per program so values are always different, seting it repeatedly to the same value (std::time(0) in one function which is called within 1 second doesn't change
    int count = 5;
    int     i = 0;

    while (++i <= count)
    {
        Base *b;
        if (i < count)
            b = generate();
        else
            b = NULL; // test last case with null poiner
        std::cout << "Identifying via pointer: ";
        identify(b);
        std::cout << "Identifying via reference: ";
        identify(*b);

        delete b;
    }
    std::cout << "Base object:" << std::endl;
	Base* baseobj = new Base;
	identify(baseobj);
	identify(*baseobj);
	delete baseobj;

    return 0;
}