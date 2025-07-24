#include "HumanA.hpp"

// constructor must have a weapon
HumanA::HumanA(const std::string& new_name, Weapon& new_weapon) : name(new_name), weapon(new_weapon)
{
    std::cout << "HumanA " << name << " constructor called." << std::endl;
};

HumanA::~HumanA()
{    
    std::cout << "HumanA " << name << " destructor called." << std::endl;
}

void HumanA::attack() const 
{
    std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}