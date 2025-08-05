#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("Animal")
{
    std::cout << "Wrong Animal default constructor called." << std::endl;
};


WrongAnimal::WrongAnimal(const WrongAnimal& origin) : type(origin.type)
{
    std::cout << "WrongAnimal copy constructor called." << std::endl;
};

WrongAnimal& WrongAnimal::operator = (const WrongAnimal& origin)
{
    std::cout << "WrongAnimal copy assignment operator called." << std::endl;
    if (this != &origin)
        this->type = origin.type;
    return *this;
};

WrongAnimal::~WrongAnimal()
{
    std::cout << "Wrong Animal destructor called." << std::endl;
};

std::string WrongAnimal::getType() const 
{
    return type;
}

void WrongAnimal::makeSound( void ) const
{
    std::cout << " ... Silence of wrong animal ... " << std::endl;
}