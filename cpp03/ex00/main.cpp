#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap bob("Bob");
    ClapTrap arthur("Arthur");

    bob.attack("Arthur");
    bob.takeDamage(5);
    bob.takeDamage(4);

    bob.beRepaired(1);
    bob.takeDamage(1);
    return 0;
}