#ifndef WEAPON_H
# define WEAPON_H

#include <iostream>
#include <string>

class Weapon
{
    private:
        std::string type;

    public:
        Weapon(const std::string& newType);
        ~Weapon();

        const std::string& getType( void ) const;
        void setType(const std::string& newType);
};

#endif