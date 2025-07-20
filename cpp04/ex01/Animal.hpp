#ifndef ANIMAL_H
# define ANIMAL_H

#include <string>
#include <iostream>

#include "Brain.hpp"

class Animal
{
    protected:
        std::string type;
    
    public:
        Animal();
        Animal(const std::string& type);
        Animal(const Animal& origin);
        Animal& operator = (const Animal& origin);
        virtual ~Animal();

        virtual void makeSound( void ) const;
        virtual Brain* getBrain() const; // will be implemented as safe default
};

#endif