#include "Dog.hpp"

Dog::Dog() : Animal::Animal("Dog")
{
    std::cout << "Dog default constructor called." << std::endl;
};

Dog::~Dog()
{
    std::cout << "Dog destructor called." << std::endl;
};

void Dog::makeSound()
{
    std::cout << "Woof! Woof!" << std::endl;
}