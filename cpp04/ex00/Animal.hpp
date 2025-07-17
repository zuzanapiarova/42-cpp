#ifndef ANIMAL_H
# define ANIMAL_H

#include <string>
#include <iostream>

class Animal
{
    protected:
        std::string type;
    
    public:
        Animal();
        Animal(std::string type);
        virtual ~Animal();

        virtual void makeSound( void );    
};

#endif