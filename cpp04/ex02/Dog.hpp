#ifndef DOG_H
# define DOG_H

#include <string>
#include <iostream>

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
    private:
        Brain *brain;

    public:
        Dog();
        Dog(const Dog& origin);
        Dog& operator = (const Dog& origin);
        ~Dog();
        
        void makeSound( void ) const;
        Brain* getBrain() const;

};

#endif