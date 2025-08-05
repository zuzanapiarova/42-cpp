#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
    // 0. test/check constructors and copying

    // 1. this works because it is not using polymorphism, functions are called directly on objects of known types
    const Animal a1;
    const Dog d1;
    std::cout << a1.getType() << " " << std::endl;
    std::cout << d1.getType() << " " << std::endl;
    a1.makeSound();
    d1.makeSound();
    std::cout << std::endl;

    // 2. Object slicing - this does not work because runtime polymorphism needs the pointer/reference, not a copy - the copy copies Dog into Animal, but slices Dog-specific part 
    const Animal a2 = Animal();
    const Animal d2 = Dog();
    std::cout << a2.getType() << " " << std::endl;
    std::cout << d2.getType() << " " << std::endl;
    a2.makeSound();
    d2.makeSound(); // dog does not bark, but uses the animal sound
    std::cout << std::endl;

    // 3. this works because it uses true polymorphism by using pointers AND the makeSound is virtual in parent
    const Animal* a3 = new Animal();
    const Animal* d3 = new Dog(); // slicing removes derived part
    std::cout << a3->getType() << " " << std::endl;
    std::cout << d3->getType() << " " << std::endl;
    a3->makeSound();
    d3->makeSound();
    std::cout << std::endl;

    // 4. same here = true polymorphism, now using references
    const Animal& a4 = *a3;
    const Animal& d4 = *d3;
    // const Dog& h = *e; // --> does not work because you can’t safely downcast a base class pointer to a derived class reference
    std::cout << a4.getType() << " " << std::endl;
    std::cout << d4.getType() << " " << std::endl;
    a4.makeSound();
    d4.makeSound();
    std::cout << std::endl;

    // 5. this is wrong - true polymorphism with pointers just like test 3., but wrongcat does not use virtual for makeSound function
    const WrongAnimal *wa = new WrongAnimal();
    const WrongAnimal *wc = new WrongCat();
    std::cout << wa->getType() << " " << std::endl;
    std::cout << wc->getType() << " " << std::endl;
    wa->makeSound();
    wc->makeSound();
    std::cout << std::endl;

    delete a3;
    delete d3;
    delete wa;
    delete wc;

    return 0;
}