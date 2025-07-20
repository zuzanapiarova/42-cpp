#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main(void)
{
    int size = 10;

    // creatin animal objects, cats and dogs
    Animal* animals[size];
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            animals[i] = new Cat();
        else
            animals[i] = new Dog();

    }
    // making sounds
    for (int i = 0; i < size; i++)
    {
        animals[i]->makeSound();
    }
    // checking for deep copies - they cannot share a brain
    Dog *dogPtr = dynamic_cast<Dog*>(animals[1]);
    if (dogPtr)
    {
        Dog* newDog = new Dog(*dogPtr);  // deep copy
        
        dogPtr->getBrain()->setIdea(0, "I am dog 1.");
        
        std::cout << "dog1 brain pointer: " << dogPtr->getBrain() << std::endl;
        std::cout << "dog2 brain pointer: " << newDog->getBrain() << std::endl;

        std::cout << dogPtr->getBrain()->getIdea(0) << std::endl;
        std::cout << newDog->getBrain()->getIdea(0) << std::endl;

        delete newDog;
    }
    else
    {
        std::cout << "animals[1] is not a Dog!" << std::endl;
    }
    // deleting the animals
    for (int i = 0; i < size; i++)
    {
        delete animals[i];
    }

    return 0;
}