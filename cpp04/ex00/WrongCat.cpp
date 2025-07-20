#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    type = "WrongCat";
    std::cout << "WrongCat constructor called\n";
}

WrongCat::WrongCat(const WrongCat& origin) : WrongAnimal(origin)
{
    std::cout << "WrongCat copy constructor called." << std::endl;
};

WrongCat& WrongCat::operator = (const WrongCat& origin)
{
    std::cout << "WrongCat copy assignment operator called." << std::endl;
};

WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called\n";
}

void WrongCat::makeSound() const
{
    std::cout << "WrongCat meows wrongly!\n";
}