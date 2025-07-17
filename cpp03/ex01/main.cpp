#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
    ClapTrap clara("Clara");
    ScavTrap sara("Sara");

    sara.attack("Clara");
    clara.attack("Sara");
    sara.takeDamage(5);
    sara.takeDamage(4);

    sara.guardGate();
    // clara.guardGate();
    return 0;
}