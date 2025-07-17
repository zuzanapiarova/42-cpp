#include "Animal.hpp"

Animal::Animal() : type("Unclassified")
{
    std::cout << "Animal default constructor called." << std::endl;
};

Animal::Animal(std::string type) : type(type)
{
    std::cout << "Animal overload constructor called." << std::endl;
};

Animal::~Animal()
{
    std::cout << "Animal destructor called." << std::endl;
};

void Animal::makeSound( void )
{
    std::cout << " ... Silence... " << std::endl;
}