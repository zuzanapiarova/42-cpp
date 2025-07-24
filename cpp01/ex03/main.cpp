#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void)
{
    // 1. HumanA has to get a Weapon by reference, because when the weapon is changed, it must be reflected in the Human whose attribute it is
    // if the reference was not passsed, then a copy of the Weapon would be created and passed to the person, and changing the original Weapon would not be reflected in the Human, since it would be a completely different object
    {
        Weapon  club("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("other type of club");
        bob.attack();
    }
    std::cout << std::endl;

    // 2. HumanB does not always have to have a weapon
    // BUT it cannot store it in a normal variable, because it would create a copy, which we do not want, and it cannot store it as a reference, becasue that would need to be initialized from the beginning of the object
    // so it has to get a Weapon by pointer - pointer allows to create the Human object without it and assign/change it later, but still passes the object, not a copy   
    {
        Weapon  club("crude spiked club");
        HumanB jim("Jim");
        jim.attack();
        jim.setWeapon(club);
        jim.attack();
        club.setType("other type of club");
        jim.attack();
    }
    std::cout << std::endl;

    return 0;
}