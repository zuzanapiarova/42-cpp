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
        WrongAnimal(const WrongAnimal& origin);
        WrongAnimal& operator = (const WrongAnimal& origin);
        virtual ~WrongAnimal();

        virtual std::string getType() const ;
        void makeSound( void ) const;

};

#endif