#include "HumanB.hpp"

// constructor without weapon
HumanB::HumanB(std::string new_name) : name(new_name), weapon(NULL) {};

// we have to pass in weapon by reference, because else it would create a copy and not reflect changes
void HumanB::setWeapon(Weapon& new_weapon)
{
    weapon = &new_weapon;
}

void HumanB::attack()
{
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    else
        std::cout << name << " has no weapon!" << std::endl;
}