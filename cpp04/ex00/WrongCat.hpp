#ifndef WRONG_CAT_H
# define WRONG_CAT_H

#include <iostream>
#include <string>

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
    public:
        WrongCat();
        WrongCat(const WrongCat& origin);
        WrongCat& operator = (const WrongCat& origin);
        virtual ~WrongCat();

        void makeSound( void ) const;
};

#endif