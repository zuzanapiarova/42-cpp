#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <iostream>
# include <string>

class Zombie
{
    private:
        std::string name;

    public:
        Zombie(); // default constructor
        Zombie(std::string name); // overload constructor with name
        ~Zombie(); // destructor

        void    announce(void);
        void    setName(std::string newName);

};

Zombie* zombieHorde(int N, std::string name);

#endif