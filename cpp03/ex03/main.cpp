#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main(void)
{
    DiamondTrap dominic("Dominic");
    std::cout << std::endl;

    dominic.attack("Fred");
    dominic.takeDamage(5);
    dominic.beRepaired(4);
    std::cout << std::endl;

    dominic.highFiveGuys();
    dominic.guardGate();
    dominic.whoAmI();
    std::cout << std::endl;

    return 0;
}