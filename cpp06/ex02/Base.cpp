#include "Base.hpp"

Base::~Base()
{
    std::cout << "Base destructor called." << std::endl;
};

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
    return new A;
}

// dynamic cast is only safe way to downcast - taking in pointer and if type is not correct, does not throw exeption, but returns nullptr, so we can check after each cast if it worked or no
void identify(Base* p)
{
    if (dynamic_cast<A*>(p)) std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p)) std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p)) std::cout << "C" << std::endl;
    else std::cout << "Unknown" << std::endl;
}

// with reference,e must use try-catch becasue it will throw bad-cast exception if type is not correct
// the result of the cast is cast to void - must be there because we have to do some operation with the casted deference to possibly trigger an exception, and it cannot be if(ref){} as with pointers, cause that is illegal since ref can never be null, and it cannot be assigned to variable, since we will not use it and will get unused variable error
void identify(Base& r)
{
    try
    {
        (void)dynamic_cast<A&>(r);
        std::cout << "A" << std::endl;
    } 
    catch (std::exception& e)
    {
        try
        {
            (void)dynamic_cast<B&>(r);
            std::cout << "B" << std::endl;
        }
        catch (std::exception& e)
        {
            try
            {
                (void)dynamic_cast<C&>(r);
                std::cout << "C" << std::endl;
            }
            catch (std::exception& e)
            {
                std::cout << "Unknown" << std::endl;
            }
        }
    }
    // try 
    // {
    //     (void)dynamic_cast<A&>(p);
    //     std::cout << "A" << std::endl;
    //     return ;
    // }
    // catch (...) {};

    // try 
    // {
    //     (void)dynamic_cast<A&>(p);
    //     std::cout << "A" << std::endl;
    //     return ;
    // }
    // catch (...) {}

    // try 
    // {
    //     (void)dynamic_cast<A&>(p);
    //     std::cout << "A" << std::endl;
    //     return ;
    // }
    // catch (...) {};

    // std::cout << "Unknown" << std::endl;
};
