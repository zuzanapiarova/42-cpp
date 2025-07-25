# CPP EXCERCISES

The 42 curriculum includes 10 C++ modules, each composed of multiple excercises directed towards a specific new topic to learn. It is composed in a way to make us, students, approach the tasks in OOP way rather that the procedural paradigm we were used to in C projects. 

Below I include tests that can come in handy during evaluations and any other important info. 

## CPP00 - Getting started with CPP syntax and classes

#### Excercise 0 - Megaphone

Simple printing of program arguments to stdout.

Tests:
1. Empty input
2. Empty quotes
3. No caps input
4. Input mixing no-caps, caps, digits, special characters
5. Multiple program argumentes - do not have to have space between when printed because in subject there are none also

#### Excercise 1 - PhoneBook

First classees, constructors, destructors, getters & setters, populating and operating a simple phonebook containing contacts via user input.

Tests:
1. empty ADD/SEARCH/EXIT commands - only enter/whitespaces
2. ctrl+D during ADD/SEARCH/EXIT commands 
3. command other than ADD/SEARCH/EXIT
4. SEARCH with empty phone book

5. ADD with empty fields
6. ctrl+D during waiting for user inputs for ADD fields
7. ADD with too long int for number field
8. ADD phone number that is not number-only
9. ADD with too long first name/last name/nickname - over 10 chars / exactly 10 chars

10. SEARCH with index being char/string
11. SEARCH with index being out of range
12. SEARCH with index being negative number
13. SEARCH with index being 0
14. SEARCH with index being empty

15. SEARCH has proper formatting of fields
16. overwriting the oldest contact when adding more than 8 contacts
17. overwriting the oldest contact when adding more than 8 contacts again - should overwrite the oldest one, not the one at index 0

## CPP01 - Pointers and references to objects, allocating on the heap

#### Excercise 0 - Lifetime of objects - Zombie on stack vs on the heap

This excercise shows us the lifetime of created objects - for allocated on the stack created by the constructor, or allocated on the heap with the new keyword.

Tests:
1. newZombie should create the zombie by allocating it and it will persist outside - test it by calling the announce function outside of tehfunction where it was created
2. randomChump should create a new zombie and announce it, it does not persist outside of the randomChump function
3. delete the newZombie at the end of program - watch order of construction/destruction - destruction should be reversed for the code below
```
int main(void)
{
    Zombie* z = newZombie("Bob");
    z->announce();

    randomChump("Alice");

    delete z;

    return 0;
}
```

#### Excercise 1 - Array of objects on the heap

This excercise is about creating arrays of objects. We learn that to inizialize an array of objects, we cannot do it at once, but we have to use default constructor and a setter.

Tests:
1. Check that the allocation of the zombie horde in the zombieHorde function happens on one line, and that the name is set only after creation with setter.
2. Check that the default constructor is called for each created zombie.
3. Check that when creating 0/negative horde size, it is handled and no leaks occur.
4. Check that it works as expected with some n zombies and they are properly freed afterwards.
5. Check that the zombieHorde returns the first objects address. 
6. Check 3.,4. with valgrind 
```
int main(void)
{
    int N;

    N = 0;
    Zombie *horde1 = zombieHorde(N, "Zero Walkers");
    for (int i = 0; i < N; i++)
        horde1[i].announce();

    N = 5;
    Zombie *horde2 = zombieHorde(N, "N Walkers");
    for (int i = 0; i < N; i++)
        horde2[i].announce();

    if (horde2 == &horde2[0])
        std::cout << "zombieHorde returns the first object."  << std::endl;
    else
        std::cout << "zombieHorde does not return the first object." << std::endl;

    delete[] horde1;
    delete[] horde2;

    return 0;
}
```

#### Excercise 2 - Variable, reference, pointer

This excercise is about showing us the difference between variables, their references and their pointers, and what is the syntax.

- variable = a specific value, stored at some address
- pointer = stores the address at which the variable is stored
- reference = alias for an existing variable — not a copy, and not a new object, just another name for the same variable

So why would we use references? 
- nmostly for performance --> to avoid creating unneccessary copies of larger objects when passing them into the functions - when using refrences, the objec itself is passed, the function does not create a copy
- and also, it is cleaner and safer than pointeres - they need to be initialized and cannot be NULL, and cleaner since we do notneed to be using & or * when accessing it, only once & when declaring it

So this is the correct implementation:
```
int main(void)
{
    std::string string = "HI THIS IS BRAIN";
    std::string *stringPTR = &string;
    std::string& stringREF = string;

    // prints addresses
    std::cout << &string << std::endl;
    std::cout << stringPTR << std::endl;
    std::cout << &stringREF << std::endl;

    // prints what is stored in the variables
    std::cout << string << std::endl;
    std::cout << *stringPTR << std::endl;
    std::cout << stringREF << std::endl;

    return 0;
}
```
And this is the correct output:
```
0x7ffdcd435a78
0x7ffdcd435a78
0x7ffdcd435a78
HI THIS IS BRAIN
HI THIS IS BRAIN
HI THIS IS BRAIN
```

#### Excercise 3 - Using objects of one class as attributes of another class

In this excercise we have a class, whose attribute is object of another class. We explore storing it as a variable, as a pointer, and as a reference. 

Storing the object as:
- variable = not good, because it will create a copy of the passed object, so changing the object later will not show a change in teh object to which it is assigned, since it is now two different objects
- reference = stores a concrete object, not its copy, but it has to be initialized and can never be NULL
- pointer = pointer also stores the concrete object, not its copy, and it does not have to have a value from the start - we can set/change it later

Tests:
1. HumanA has to get a Weapon by reference, because when the weapon is changed, it must be reflected in the Human whose attribute it is
- if the reference was not passsed, then a copy of the Weapon would be created and passed to the person, and changing the original Weapon would not be reflected in the Human, since it would be a completely different object

2. HumanB does not always have to have a weapon
- BUT it cannot store it in a normal variable, because it would create a copy, which we do not want, and it cannot store it as a reference, becasue that would need to be initialized from the beginning of the object
- so it has to get a Weapon by pointer - pointer allows to create the Human object without it and assign/change it later, but still passes the object, not a copy  

```
int main(void)
{
    //1. 
    {
        Weapon  club("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("other type of club");
        bob.attack();
    }
    std::cout << std::endl;

    // 2. 
    {
        Weapon  club("crude spiked club");
        HumanB jim("Jim");
        jim.attack();
        jim.setWeapon(club);
        jim.attack();
        club.setType("other type of club");
        jim.attack();
    }
    std::cout << std::endl;

    return 0;
}
```

#### Excercise 4 - Sed - reading and writing to files

In this excercise we practiced using streams for file manipulation, as C file manipulation functions that the students know how to use are forbidden.

- #include <fstream>
- std::ifstream inputFile("input.txt") - used to read from files - create input stream
- std::ofstream  outputFile("output.txt") - used to write to files - create output stream

Tests:
1. Number of program arguments different than 4
2. Input file does not exist
3. Input files des not have read permissions
4. Output file exists but does not have write permissions
5. String to be replaced is ""
6. String to replace is ""
7. Normal input to be replaced, upper and lowercase versions of the string

#### Excercise 5 - Harl - Pointers to member functions

This excercise showed us how to create and work with function pointers. With member function pointers, we can pass a function of a specific class as an argument to another function. Member functions differ from regular functions because they are associated with an instance of a class, which means they have an implicit this pointer that points to the object, invoking the object, and they cannot be called without an object. They are used to dynamically call different member functions of a class based on runtime decisions, and avoid lots of if/else statements.

Pointers to functions are declared as:
` <void> Classname::*functionPointer() = &ClassName::memberFunction `
And they are called like:
`(this->*function)() `

Tests:
1. The complain() public function should do somehing like above - declare and call appropriate member function, in a loop, without using a lot of if statements
```
int main(void)
{
    Harl harl;

    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    // 1. testing correct input
    for (int i = 0; i < 10; i++)
        harl.complain(levels[i%4]);
    
    // 2. testing wrong input
    harl.complain("SOME");
    harl.complain("WRONG");
    harl.complain("LEVELS");
    
    return 0;
}
```

#### Excercise 6 - Harl - switch

Learned to use seitch case statements. Use switch with fallthrough - no break for lower levels, only the last one, because the upper levels should still be printed anyways.

Tests:
1. Check program with no arguments
2. Check program with more than 1 argument
3. Check with empty quotes
4. Check with wrong argument - other than DEBUG/INFO/WARNING/ERROR
5. Check it correctly prints all messages after the one we specify, else nothing. 
6. The complain fuction must be using switch-case syntax with fallthrough

## CPP05 - Exceptions, Abstract classes, overriding of abstract class methods

#### Excercise 0 - 

#### Excercise 1 - 

#### Excercise 2 - Overriden Forms inheriting from abstract class AForm

Making an abstract class and making 3 classes that inherit from it. Must raise appropriate exceptions.

Possible exceptions:
1. Creating Bureaucrat object with too low/high grade (other than range 1-150)
2. Bureaucrat trying to sign/execute form with not enough high grade
3. Trying to execute unsigned form
4. Check that AForm attributes are private, not protected

Tests:
0. Create a bureaucrat 
```
    Bureaucrat a("Anna", 6);
    Bureaucrat b("Bob", 160); // will not be created beacsue grade for creation is too high
    std::cout << a << std::endl << std::endl;
```
1. Sign and execute actions should both work - bureaucrat has enough grade
```
    ShrubberyCreationForm s("Garden");
    std::cout << s << std::endl << std::endl;
    a.signForm(s); // works - Anna has access to sign
    a.executeForm(s); // works - Anna has access to execute
    std::cout << s << std::endl << std::endl;
```
2. Execute should not work - form is not signed yet - sign and then it it should execute
```
    RobotomyRequestForm r("Smart Robot");
    a.executeForm(r); // does not work - Form is not signed yet 
    a.signForm(r); // sign the form
    a.executeForm(r); // signed the form, now it works, Anna has execute acess
    std::cout << r << std::endl << std::endl;
```
3.  Sign should work, but not enough grade for execution - increment grade and then it should work
```
    PresidentialPardonForm p("Pardoned Person");
    a.signForm(p); // Anna can sign teh form, she has access
    a.executeForm(p); // but she does not have execute access, so it throws an exception
    a.incrementGrade(); // increment Anna's grade so she has access to execute
    a.executeForm(p); // now it works, Anna has execute access
    std::cout << p << std::endl << std::endl;
```

#### Excercise 3 - Function pointers again

This excercise is about creating a small but more extensive program where multiple classes interact. 

Tests:
1. Check how the makeForm is creating different forms - cannot have many if statements
2. If created with new, check with valgrind.
3. Test creation of all 3 forms by the intern.
4. Test all 3 forms being usable by bureaucrats - try to sign and execute. 

```
int main(void)
{
    Intern i;
    
    AForm* first = i.makeForm("shrubbery creation", "Garden");
    AForm* second = i.makeForm("robotomy request", "Smart Robot");
    AForm* third = i.makeForm("presidential pardon", "Pardoned person");

    Bureaucrat a("Anna", 1);
    a.signForm(*first);
    a.signForm(*second);
    a.signForm(*third);

    a.executeForm(*first);
    a.executeForm(*second);
    a.executeForm(*third);

    delete first;
    delete second;
    delete third;

    return 0;
}
```

## CPP05 - Casting

#### Excercise 0 - Function pointers again