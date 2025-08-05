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
        Animal(const Animal& origin);
        Animal& operator = (const Animal& origin);
        virtual ~Animal();

        virtual std::string getType() const ;
        virtual void makeSound( void ) const ;    
};

#endif