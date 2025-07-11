#ifndef WEAPON_H
# define WEAPON_H

#include <iostream>
#include <string>

class Weapon
{
    private:
        std::string type;

    public:
        Weapon(std::string weapon_type);

        const std::string& getType() const;
        void setType(std::string);
};

#endif