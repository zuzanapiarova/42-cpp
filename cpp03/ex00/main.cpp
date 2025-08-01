#include "ClapTrap.hpp"

int main(void)
{
    // check default constructor
    ClapTrap anonym;
    anonym.beRepaired(1);

    // check overload constructors
    ClapTrap arthur("Arthur");
    ClapTrap bob("Bob");

    // check member functions
    bob.attack("Arthur");
    bob.takeDamage(9);
    bob.takeDamage(1);
    bob.beRepaired(1); // should not work - low health
    bob.attack("Arthur"); // should not work - low health

    // check copy constuctor and copy assignmnent operator - name is the same - copied from Bob
    ClapTrap bob2(bob);
    anonym = bob;
    bob2.beRepaired(1); // should not work - copied zero health from Bob
    anonym.beRepaired(1); // should not work - copied zero health from Bob

    return 0;
}