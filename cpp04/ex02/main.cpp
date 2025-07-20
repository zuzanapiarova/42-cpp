#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main(void)
{
    //const Animal* d = new Animal();
    const Animal* e = new Dog(); // slicing removes derived part
    //d->makeSound();
    e->makeSound();
    //delete d;
    delete e;

    return 0;
}