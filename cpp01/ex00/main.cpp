#include "Zombie.hpp"

int main(void)
{
    Zombie* z = newZombie("Bob");
    z->announce();

    randomChump("Alice");

    delete z;  // Don't forget to delete it!
    return 0;
}