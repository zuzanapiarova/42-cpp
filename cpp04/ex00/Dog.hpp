#ifndef DOG_H
# define DOG_H

#include <string>
#include <iostream>

#include "Animal.hpp"

class Dog : public Animal
{
    public:
        Dog();
        virtual ~Dog();
        
        void makeSound( void );
};

#endif