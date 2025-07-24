#include "Zombie.hpp"

// default constructor
Zombie::Zombie() : name("")
{
    std::cout << "Default constructor called for zombie." << std::endl;
};


// overload constructor
Zombie::Zombie(std::string& newName) : name(newName)
{
    if (name.empty())
        name = "UnnamedZombie";
    std::cout << "Overload constructor called for zombie " << name << std::endl;
};

// destructor
Zombie::~Zombie()
{
    std::cout << "Destructor called for zombie " << name << std::endl;
};

void Zombie::announce(void) const 
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string& newName)
{
    name = newName;   
}

