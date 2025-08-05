#include "Dog.hpp"

Dog::Dog() : Animal::Animal(), brain(brain = new Brain())
{
    std::cout << "Dog default constructor called." << std::endl;
    type = "Dog";
};

Dog::Dog(const Dog& origin) : Animal(origin), brain(new Brain(*origin.brain))
{
    std::cout << "Dog copy constructor called." << std::endl;
};

Dog& Dog::operator = (const Dog& origin)
{
    std::cout << "Dog copy assignment operator called." << std::endl;
    if (this != &origin)
    {
        delete brain;
        brain = new Brain(*origin.brain);
        type = origin.type;
    }
    return *this;
};

Dog::~Dog()
{
    std::cout << "Dog destructor called." << std::endl;
    delete brain;
};

void Dog::makeSound() const
{
    std::cout << "Woof! Woof!" << std::endl;
};

Brain* Dog::getBrain() const
{
    return brain;
}