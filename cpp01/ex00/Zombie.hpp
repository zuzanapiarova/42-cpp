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

};

Zombie* newZombie( std::string name);
void    randomChump( std::string name);

#endif