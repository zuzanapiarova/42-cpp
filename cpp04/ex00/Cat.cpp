#include "Cat.hpp"

Cat::Cat() : Animal::Animal("Cat")
{
    std::cout << "Cat default constructor called." << std::endl;
};

Cat::~Cat()
{
    std::cout << "Cat destructor called." << std::endl;
};

void Cat::makeSound()
{
    std::cout << "Meow! Meow!" << std::endl;
}