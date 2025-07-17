#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
    Animal a;
    Dog d;
    Cat c;

    a.makeSound();
    c.makeSound();
    d.makeSound();
}