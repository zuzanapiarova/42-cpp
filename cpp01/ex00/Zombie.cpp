#include "Zombie.hpp"

// overload constructor
Zombie::Zombie(std::string name) : name(name)
{
    if (name.empty())
        this->name = "UnnamedZombie";
    std::cout << "Constructor called for zombie " << this->name << std::endl;
};

// destructor
Zombie::~Zombie()
{
    std::cout << "Destructor called for zombie " << name << std::endl;
};

void Zombie::announce(void)
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

