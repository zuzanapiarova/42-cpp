#include "Cat.hpp"

// Animal is contructed first, then type is set to Cat after initialization - BUT it is set for the Animal object, since Cat des not have its own type variable - so it will persist its value "Cat" after slicing 
// cannot do Cat::Cat() : Animal::Animal(), type("Cat") because Animal variabels are protected co Cat cannot access it 
Cat::Cat() : Animal::Animal() 
{
    std::cout << "Cat default constructor called." << std::endl;
    type = "Cat";
};

Cat::Cat(const Cat& origin) : Animal(origin)
{
    std::cout << "Cat copy constructor called." << std::endl;
};

Cat& Cat::operator =(const Cat& origin)
{
    std::cout << "Animal copy assignment operator called." << std::endl;
    if (this != &origin)
        Animal::operator =(origin);
    return *this;
};

Cat::~Cat()
{
    std::cout << "Cat destructor called." << std::endl;
};

void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
};