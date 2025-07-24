#include "Zombie.hpp"

int main(void)
{
    // 1. newZombie should create the zombie by allocating it and it will persist outside - test it by calling the announce function outside of tehfunction where it was created
    Zombie* z = newZombie("Bob");
    z->announce();

    // 2. randomChump should create a new zombie and announce it, it does not persist outside of the randomChump function
    randomChump("Alice");

    // 3. delete the newZombie at the end of program - watch order of construction/destruction
    delete z;

    return 0;
}