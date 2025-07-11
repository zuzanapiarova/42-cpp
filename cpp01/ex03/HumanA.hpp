#ifndef HUMAN_A
# define HUMAN_A

#include "Weapon.hpp"

#include <iostream>
#include <string>

class HumanA
{
    private:
        std::string name;
        Weapon& weapon; // pass in the weapon as reference - does not create a copy, but passes a function the same object

    public:
        HumanA(std::string new_name, Weapon& new_weapon);

        void attack();
};

#endif