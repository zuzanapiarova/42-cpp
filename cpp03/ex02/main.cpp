#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
    ClapTrap clara("Clara");
    ScavTrap sara("Sara");
    FragTrap fred("Fred");

    fred.attack("Clara");
    sara.attack("Fred");
    clara.attack("Sara");
    fred.takeDamage(5);
    fred.takeDamage(4);

    fred.highFiveGuys();
    // fred.guardGate(); // cannot access functon of other child class
    // sara.highFiveGuys(); // cannot access function of other child class
    // clara.guardGate(); // base class cannot access function of child class
    return 0;
}