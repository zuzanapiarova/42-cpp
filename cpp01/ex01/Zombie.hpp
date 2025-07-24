#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <iostream>
# include <string>

class Zombie
{
    private:
        std::string name;

    public:
        Zombie(); // default constructor is needed because we cannot do single-line array of objects initialization with the overload constructor - have to use default + setter
        Zombie(std::string& newName); // overload constructor with name
        ~Zombie(); // destructor

        void    announce(void) const ;
        void    setName(std::string& newName);

};

Zombie* zombieHorde(int N, std::string name);

#endif