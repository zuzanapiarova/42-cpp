#include "Animal.hpp"

Animal::Animal() : type("Unclassified")
{
    std::cout << "Animal default constructor called." << std::endl;
};

Animal::Animal(const std::string& type) : type(type)
{
    std::cout << "Animal overload constructor called." << std::endl;
};

Animal::Animal(const Animal& origin)
{
    std::cout << "Animal copy constructor called." << std::endl;
    this->type = origin.type;
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

Brain* Animal::getBrain() const
{
    std::cout << "Animal " << type << " has no brain." << std::endl;
    return nullptr; 
}