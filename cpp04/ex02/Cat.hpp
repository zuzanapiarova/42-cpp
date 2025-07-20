#ifndef CAT_H
# define CAT_H

#include <iostream>
#include <string>

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
    private:
        Brain *brain;

    public:
        Cat();
        Cat(const Cat& origin);
        Cat& operator = (const Cat& origin);
        ~Cat();

        void makeSound( void ) const;
        Brain* getBrain() const;

};

#endif