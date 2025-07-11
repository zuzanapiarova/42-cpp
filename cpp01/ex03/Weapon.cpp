#include "Weapon.hpp"

Weapon::Weapon(std::string weapon_type)
{
    type = weapon_type;
}

const std::string& Weapon::getType() const
{
    return type;
}

void Weapon::setType(std::string weapon_type)
{
    type = weapon_type;
}