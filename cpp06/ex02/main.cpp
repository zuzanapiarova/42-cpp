#include "Base.hpp"

// generates object of one of A,B,C classes
Base* generate( void )
{
    int r = std::rand() % 3;
    switch (r)
    {
        case 0: return new A;
        case 1: return new B;
        case 2: return new C;
    }
    return nullptr;
}

// dynamic cast is only safe way to downcast - taking in pointer and if type is not correct, does not throw exeption, but returns nullptr, so we can check after each cast if it worked or no
void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

// with reference,e must use try-catch becasue it will throw bad-cast exception if type is not correct, so if checking for multiple times, it must be within the catch block
// the result of the cast is cast to void - must be there because we have to do some operation with the casted deference to possibly trigger an exception, and it cannot be it (ref), cause that is illegal, and it cannot be assigned ot variable, since we will not use it and will get unused variable error
void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    } catch (...)
    {
        try
        {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
        }
        catch (...)
        {
            try
            {
                (void)dynamic_cast<C&>(p);
                std::cout << "C" << std::endl;
            } catch (...)
            {
                std::cout << "Unknown" << std::endl;
            }
        }
    }
}

// tests
// 1. try to cast other class into identify
// 2. test idenfity with pointer with nullptr
int main()
{
    std::srand(static_cast<unsigned int>(std::time(0))); // set the seed of the pseudo-random number generator once per program so values are always different, seting it repeatedly to the same value (std::time(0) in one function which is called within 1 second doesn't change
    int count = 3;
    int     i = 0;

    while (++i <= count)
    {
        Base *b;
        if (i < count)
            b = generate();
        else
            b = nullptr; // test last case with null poiner
        std::cout << "Identifying via pointer: ";
        identify(b);
        std::cout << "Identifying via reference: ";
        identify(&(*b));

        delete b;
    }
    return 0;
}