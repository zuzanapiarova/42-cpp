#include "Zombie.hpp"

int main(void)
{
    int N;

    // 1. error handling - ensure wrong input as 0 or negative is handled, deleted, and no leaks occur 
    N = 0;
    Zombie *horde1 = zombieHorde(N, "Zero Walkers");
    for (int i = 0; i < N; ++i)
        horde1[i].announce();

    // 2. correct input - ensure the zombie horde is created, all of them are accessible, and that they can be deleted
    N = 5;
    Zombie *horde2 = zombieHorde(N, "N Walkers");
    for (int i = 0; i < N; ++i)
        horde2[i].announce();
    
    // 3. check if the zombieHorde returns pointer to the first object by calling its announce:
    if (horde2 == &horde2[0])
        std::cout << "zombieHorde returns the first object."  << std::endl;
    else
        std::cout << "zombieHorde does not return the first object." << std::endl;


    delete[] horde1;
    delete[] horde2;

    return 0;
}