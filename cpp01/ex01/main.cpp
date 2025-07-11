#include "Zombie.hpp"

int main(void)
{
    int N = 0;
    Zombie *horde1 = zombieHorde(N, "Zero Walkers");
    for (int i = 0; i < N; i++)
        horde1[i].announce();

    N = 5;
    Zombie *horde2 = zombieHorde(N, "N Walkers");
    for (int i = 0; i < N; i++)
        horde2[i].announce();

    delete[] horde1;
    delete[] horde2;
    return 0;
}