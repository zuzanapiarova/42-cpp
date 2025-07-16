#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Anonym"), health(10), energy(10), damage(0) {};    

ClapTrap::ClapTrap(std::string new_name)  : name(new_name), health(10), energy(10), damage(0) {};

ClapTrap::ClapTrap(ClapTrap& origin)
{
    this->name = origin.name;
    this->health = origin.health;
    this->energy = origin.energy;
    this->damage = origin.damage;
}

ClapTrap& ClapTrap::operator = (const ClapTrap& origin)
{
    if (this != &origin)
    {    
        this->name = origin.name;
        this->health = origin.health;
        this->energy = origin.energy;
        this->damage = origin.damage;
    }
    return *this;
}

ClapTrap::~ClapTrap() {};

void ClapTrap::attack(const std::string& target)
{
    if (energy >= 1 && health > 0)
    {
        std::cout << name << "" ;
        //target->health -=  damage; // !!!!!!!!!!!
        energy -= 1;
    }
}

void ClapTrap::takeDamage(unsigned int amount)
{

}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (energy >= 1 && health > 0)
    {
        health += amount;
        energy -= 1;
    }
}