#ifndef WRONG_ANIMAL_H
# define WRONG_ANIMAL_H

#include <iostream>
#include <string>

class WrongAnimal
{
    protected:
        std::string type;
    
    public:
        WrongAnimal();
        WrongAnimal(const std::string& type);
        WrongAnimal(const WrongAnimal& origin);
        WrongAnimal& operator = (const WrongAnimal& origin);
        virtual ~WrongAnimal();

        void makeSound( void ) const;

};

#endif