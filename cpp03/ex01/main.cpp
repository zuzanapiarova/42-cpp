#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    ClapTrap arthur("Arthur");
    ScavTrap bob("Bob");

    bob.attack("Arthur");
    bob.takeDamage(5);
    bob.takeDamage(4);

    bob.beRepaired(1);
    bob.takeDamage(1);
    return 0;
}