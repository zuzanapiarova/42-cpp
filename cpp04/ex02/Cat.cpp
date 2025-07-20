#include "Cat.hpp"

Cat::Cat() : Animal::Animal("Cat")
{
    brain = new Brain();
    std::cout << "Cat default constructor called." << std::endl;
};

Cat::Cat(const Cat& origin) : Animal(origin)
{
    std::cout << "Cat copy constructor called." << std::endl;
    brain = new Brain(*origin.brain);
};

Cat& Cat::operator = (const Cat& origin)
{
    std::cout << "Cat copy assignment operator called." << std::endl;
    if (this != &origin)
    {
        delete brain; // delete brain from default constructor
        brain = new Brain(*origin.brain); // create deep copy of brain
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