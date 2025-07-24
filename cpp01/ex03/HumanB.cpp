#include "HumanB.hpp"

// constructor without weapon
HumanB::HumanB(const std::string& new_name) : name(new_name), weapon(NULL)
{
    std::cout << "HumanB " << name << " constructor called." << std::endl;
};

HumanB::~HumanB()
{    
    std::cout << "HumanB " << name << " destructor called." << std::endl;
};

// we have to pass in weapon by reference, because else it would create a copy and not reflect changes
void HumanB::setWeapon(Weapon& new_weapon)
{
    weapon = &new_weapon; // here, this->weapon is a pointer, so we have to provide it the address of the weapon reference
}

void HumanB::attack() const
{
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    else
        std::cout << name << " has no weapon!" << std::endl;
}