#include "Dog.hpp"

Dog::Dog() : Animal::Animal()
{
    std::cout << "Dog default constructor called." << std::endl;
    type = "Dog";
};

Dog::Dog(const Dog& origin) : Animal(origin)
{
    std::cout << "Dog copy constructor called." << std::endl;
};

Dog& Dog::operator = (const Dog& origin)
{
    std::cout << "Dog copy assignment operator called." << std::endl;
    if (this != &origin)
        Animal::operator =(origin);
    return *this;
};

Dog::~Dog()
{
    std::cout << "Dog destructor called." << std::endl;
};

void Dog::makeSound() const
{
    std::cout << "Woof! Woof!" << std::endl;
}