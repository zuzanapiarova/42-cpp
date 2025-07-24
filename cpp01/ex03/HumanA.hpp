#ifndef HUMAN_A
# define HUMAN_A

#include <iostream>
#include <string>

#include "Weapon.hpp"

class HumanA
{
    private:
        std::string name;
        Weapon& weapon; // pass in the weapon as reference - does not create a copy, but passes a function the same object

    public:
        HumanA(const std::string& new_name, Weapon& new_weapon);
        ~HumanA();

        void attack() const;
};

#endif