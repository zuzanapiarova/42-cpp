#ifndef HUMAN_B
# define HUMAN_B

#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanB {
    private:
        std::string name;
        // HumanB has pointer to weapon object since weapon is optional - pointer allows to create the Human object without it and assign/change it later, but still passes the object, not a copy
        // if there was reference, it would have to be initialized immediately in the constructor initializer list since we cannot have an uninitialized reference
        // if there was weapon itself, it would make a copy of that object, and if the weapon changed later, HumanB would not see the new value 
        Weapon* weapon; 
    
    public:
        HumanB(std::string new_name); // constructor without weapon
    
        void attack();
        void setWeapon(Weapon& new_weapon);
};

#endif