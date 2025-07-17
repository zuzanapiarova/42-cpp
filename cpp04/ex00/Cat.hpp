#ifndef CAT_H
# define CAT_H

#include <iostream>
#include <string>

#include "Animal.hpp"

class Cat : public Animal
{
    public:
        Cat();
        ~Cat();

        void makeSound( void );
};

#endif