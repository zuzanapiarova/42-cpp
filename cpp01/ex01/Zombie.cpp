#include "Zombie.hpp"

// dfault constructor
Zombie::Zombie() {};

// overload constructor
Zombie::Zombie(std::string name) : name(name) {};

// destructor
Zombie::~Zombie()
{
    std::cout << "Destructor called for zombie " << name << std::endl;
};

void Zombie::announce(void)
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string newName)
{
    name = newName;   
}

