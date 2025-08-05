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
        Animal(const Animal& origin);
        Animal& operator = (const Animal& origin);
        virtual ~Animal();

        virtual std::string getType() const ;
        virtual void makeSound( void ) const = 0;
        virtual Brain* getBrain() const; // will be implemented as safe default
};

#endif