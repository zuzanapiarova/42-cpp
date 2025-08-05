#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main(void)
{
    int size = 4;

    // A. Checking order of const./dest. AND proper destruction (virtual destructor in parent)
    std::cout << " ------> Checking destructors - run with valgrind. <------" << std::endl;
    // creating animal objects, cats and dogs
    Animal* animals[size];
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    std::cout << std::endl;

    // making sounds
    for (int i = 0; i < size; i++)
        animals[i]->makeSound();
    std::cout << std::endl;

    // deleting the animals
    for (int i = 0; i < size; i++)
        delete animals[i];
    std::cout << std::endl;

    // B. checking they do not share brains
    std::cout << " -----> Checking animals do not share the same brains. <------" << std::endl;
    // checking for deep copies - they cannot share a brain
    Dog Becky;
    Becky.getBrain()->setIdea(0, "I love cats.");
    Dog Lucky(Becky);
    std::cout << std::endl;

    std::cout << "Becky brain pointer: " << Becky.getBrain() << std::endl;
    std::cout << "Lucky brain pointer: " << Lucky.getBrain() << std::endl;

    std::cout << "Becky thinks: " << Becky.getBrain()->getIdea(0) << std::endl;
    std::cout << "Lucky thinks: " << Lucky.getBrain()->getIdea(0) << std::endl;

    Lucky.getBrain()->setIdea(0, "I hate cats.");

    std::cout << "Becky now thinks: " << Becky.getBrain()->getIdea(0) << std::endl;
    std::cout << "Lucky now thinks: " << Lucky.getBrain()->getIdea(0) << std::endl;

    std::cout << std::endl;

    //Animal animal; - not possible 

    return 0;
}