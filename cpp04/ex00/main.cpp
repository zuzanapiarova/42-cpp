#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
    // this works because it is not using polymorphism, functions are called directly on objects of known types
    const Animal a;
    const Dog b;
    a.makeSound();
    b.makeSound();

    // Object slicing - this does not work becasue runtime polymorphism needs the pointer/reference, not a copy - dog does not bark, but uses the animal sound
    const Animal x = Animal();
    const Animal c = Dog();
    x.makeSound();
    c.makeSound();

    // this works because it uses polymorphism and pointers
    const Animal* d = new Animal();
    const Animal* e = new Dog(); // slicing removes derived part
    d->makeSound();
    e->makeSound();

    // same here = true polymorphism, now using references
    const Animal& f = *d;
    const Animal& g = *e;
    // const Dog& h = *e; // --> does not work because you can’t safely downcast a base class pointer to a derived class reference
    f.makeSound();
    g.makeSound();

    // this is wrong - wrongcat does not use virtual
    const WrongAnimal *h = new WrongAnimal();
    const WrongCat *i = new WrongCat();
    h->makeSound();
    i->makeSound();
    
    delete d;
    delete e;
    delete h;
    delete i;

    return 0;
}