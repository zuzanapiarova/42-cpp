#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("Unclassified")
{
    std::cout << "Wrong Animal default constructor called." << std::endl;
};

WrongAnimal::WrongAnimal(const std::string& type) : type(type)
{
    std::cout << "Wrong Animal overload constructor called." << std::endl;
};

WrongAnimal::WrongAnimal(const WrongAnimal& origin)
{
    std::cout << "WrongAnimal copy constructor called." << std::endl;
    this->type = origin.type;
};

WrongAnimal& WrongAnimal::operator = (const WrongAnimal& origin)
{
    std::cout << "WrongAnimal copy assignment operator called." << std::endl;
    if (this != &origin)
        this->type = origin.type;
};

WrongAnimal::~WrongAnimal()
{
    std::cout << "Wrong Animal destructor called." << std::endl;
};

void WrongAnimal::makeSound( void ) const
{
    std::cout << " ... Silence of wrong animal ... " << std::endl;
}