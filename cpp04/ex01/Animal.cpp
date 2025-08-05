#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
    std::cout << "Animal default constructor called." << std::endl;
};

// Animal does not have overload constructor - it always has the default type Animal

Animal::Animal(const Animal& origin) : type(origin.type) // what will happen if i create animal from cat/dog, or vice versa? 
{
    std::cout << "Animal copy constructor called." << std::endl;
};

Animal& Animal::operator = (const Animal& origin)
{
    std::cout << "Animal copy assignment operator called." << std::endl;
    if (this != &origin)
        this->type = origin.type;
    return *this;
};

Animal::~Animal()
{
    std::cout << "Animal destructor called." << std::endl;
};

std::string Animal::getType() const
{
    return type;
};


void Animal::makeSound( void ) const
{
    std::cout << " ... Unidentifiable sound ... " << std::endl;
};

Brain* Animal::getBrain() const
{
    std::cout << "Animal " << type << " has no brain." << std::endl;
    return nullptr; 
};