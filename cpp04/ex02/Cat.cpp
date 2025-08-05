#include "Cat.hpp"

Cat::Cat() : Animal::Animal(), brain(new Brain())
{
    std::cout << "Cat default constructor called." << std::endl;
    type = "Cat";
};

Cat::Cat(const Cat& origin) : Animal(origin), brain(new Brain(*origin.brain))
{
    std::cout << "Cat copy constructor called." << std::endl;
};

Cat& Cat::operator = (const Cat& origin)
{
    std::cout << "Cat copy assignment operator called." << std::endl;
    if (this != &origin)
    {
        delete brain;
        brain = new Brain(*origin.brain);
        type = origin.type;
    }
    return *this;
};

Cat::~Cat()
{
    std::cout << "Cat destructor called." << std::endl;
    delete brain;
};

void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return brain;
}