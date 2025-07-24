#include "Weapon.hpp"

Weapon::Weapon(const std::string& newType) : type(newType)
{
    std::cout << "Weapon " << type << " constructor called." << std::endl;
}

Weapon::~Weapon()
{
    std::cout << "Weapon " << type << " destructor called." << std::endl;
}

const std::string& Weapon::getType( void ) const
{
    return type;
}

void Weapon::setType(const std::string& newType)
{
    type = newType;
}