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
8. File is empty

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

## CPP02 - Classes, objects, orthdox cannonical form, overloading (polymorphism)

#### Excercise 0 - Orthodocx cannonical form, static variable members

This excercise should make us used to using the orthodox cannonical form. Namely, for 42 cursus we must always implement a default constructor, overload constructor (when needed), copy constructor, copy assignment operator, and destructor, all with appropriate messages. 

Some best practices:
0. Always use namespace of the class when implementing its functions, constructors, destructors, or defining static members. 
1. Default constructor: declare variables with () afterwards, even if empty, so they are value-initialized for default values for that type: Fixed::Fixed() : value(). Called automatically, even if not defined.
2. Copy constructor = do NOT assign with = as *this = origin, because the object is not yet fully constructed. Rather directly initialize members using the copy constructor's member initializer list as this->value = origin.value.
3. Copy assignment operator - always check if it is not the same object with (this != origin), and only then perform the assignment of members to origin members - because if we were using new/delete, we would delete the existing objects member. Also, always return *this. 
4. Default constructor = called automatically, even if not defined, when the scope of the object finishes (end of function/end of program).

Static variables are tied to the class, not the object, so all instances of a class share the same memory for that variable, and change in one is reflected in others. Static members must be defined outside the class, in namespace of that class, without the static keyword.

Tests:
1. Default constructor 
2. Copy constructor
3. Copy assignment operator
4. Check all 3 object's value with getRawBits - should be 0
5. Set all 3 object's value with setRawBits and print afterwards
```
int main(void)
{
    Fixed a;        // default constructor
    Fixed b( a );   // copy constructor

    Fixed c;
    c = b;          // copy assignment operator

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    a.setRawBits(42);
    b.setRawBits(15);
    c.setRawBits(-50);

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    return 0;
}
```

#### Excercise 01 - Overload constructors, data types, bits mapping

This excercise introduces overlaod constructors to construct the object from differnet data types by calling the same function, so the functionality depends just on the type of arguments. 

We also work with bits and how they store numbers in memory. 
 0 0000000 00000000 00000000.00000000
 -|      integer part       | fractional part|

- integer part: is 2^23 --> 32 bits integer, -8 for fractional part, -1 for the sign bit
- fractional part (after the dot) : those are also multiples of 2 - just negative: they go 2^-1 for the first fractional bit, to 2^-8 for the last fractional bit. 

Storing floats is more tricky:
The value, when storing floats, is not exact. Because in fixed-point with 8 fractional bits, the smallest fractional step is 2^-8 = 1 / 2^8 = 1 / 256 = 0.00390625. So numbers which are not 2^-1 - 2^-8 or their multiplies will always have some rounding error.
1. float input is 1234.4321f
2. it is first shifted by 8 to left (multiplied by 256) to store it as 32bit integer = 316020.6336
3. it has to be rounded to be stored as integer = roundf(316020.6336) = 316021
4. when converting back to float for display: 316021 >> 256 = 1234.43359375 - because it was rounded to be stored as integer, the value will not be the same, unless it 

Tests:
0. Test default constructor, overload constructor for float, overload constructor for int, copy constructor, copy assignment operator. 
1. Handle the max raw value received - even if the maxint fits in the value, the last 8 bits are reserved for the fractional part, so the maximum value we can receive into the rawValue is between <-8388608, 8388607>, else it would wrap and not properly represent the fixed point. 
! when clamping to int_max value, and then doing << fractional_bits, is is rounded and float then rounds it to higher when printing, but internally it is still represented as max int

#### Excercise 02 - Overloading operators and basic functions

In this excerciwe we have to implement how the class Fixed behaves with operators (arithmetic, comparison, pre/post increment/decrement, max & min function) by overloading. 

When multiplying two fixed-point numbers, which is multiplying two scaled values, it results in an extra scaling and the result must be shifted right by fractional_bits to correct it.
(a << 8) * (b << 8) = ( a * b ) << 16

Same for division, but the opposite direction: to maintain fixed-point precision, value must be shifted left before dividing to avoid losing the fractional part. 

Pre-increment (++a) operator modifies the object (*this) in-place and returns a reference to the current object (*this), so you can chain operations or observe the updated value immediately. 
Post-increment (a++) operator, on the other hand, must return the original value before the increment, so it makes a copy of the current object, then increments the current one. You cannot return a reference here because the result is a temporary copy — returning a reference to that would be unsafe and incorrect. Also, the int in signature is just a dummy to differentiate it from pre-increment.

Min/max functions don't depend on any internal state of a specific Fixed object (which they shouldn't), so they should be declared static. Compiler can optimize static functions better since there’s no this pointer involved.

Test:
0. Test all basic functions AND also check with const members
- edge cases test: these cannot wrap !
1. Add 2 numbers that result in value smaller/larger than int
2. Extract 2 numbers that result in value smaller/larger than int
3. Multiply 2 numbers that result in value smaller/larger than int
4. Multiply 2 numbers that result in value smaller/larger than 1^-31 (0.00390625)
5. Divide by 0 - not mandatory by the subject
6. Divide 2 numbers such that result is smaller/larger than int
```
int main(void)
{
    std::cout << std::fixed << std::setprecision(8); // disables scientific notation
    std::cout << "Max value: " << Fixed::max_raw_value << std::endl;
    std::cout << "Max input: " << Fixed::max_input << std::endl;

    // A. basic tests + tests const
    Fixed a(10);
    Fixed const b( 5.05f );
    Fixed const c( 3 );
    Fixed const d( Fixed( 5.05f ) * Fixed( 2 ) );
    
    std::cout << "Smaller: " << (a < b) << std::endl;
    std::cout << "Greater: " << (a > b) << std::endl;
    std::cout << "< or eq: " << (a <= b) << std::endl;
    std::cout << "> or eq: " << (a >= b) << std::endl;
    std::cout << "Equals : " << (a == b) << std::endl;
    std::cout << "Not eq : " << (a != b) << std::endl;
    
    std::cout << "Plus  : " << (a + b) << std::endl;
    std::cout << "Minus : " << (a - b) << std::endl;
    std::cout << "Multi : " << (a * b) << std::endl;
    std::cout << "Divide: " << (a / b) << std::endl;

    std::cout << "Increment: " << ++a << std::endl;
    std::cout << "Decrement: " << a++ << std::endl;

    std::cout << "Min : " << Fixed::min( a, b ) << std::endl;
    std::cout << "Max : " << Fixed::max( a, b ) << std::endl;

    std::cout << "Min const: " << Fixed::min( c, d ) << std::endl;
    std::cout << "Max const: " << Fixed::max( c, d ) << std::endl;

    // B. edge-case tests - error/clamping
    Fixed e(8388607);
    Fixed f(-8388608);
    Fixed g(0.00390625f);

    std::cout << "Plus > int : " << (e + e) << std::endl;
    std::cout << "Plus < int : " << (f + f) << std::endl;
    std::cout << "Minus > int : " << (e - f) << std::endl;
    std::cout << "Minus < int : " << (f - e) << std::endl;
    std::cout << "Multi > int : " << (e * e) << std::endl;
    std::cout << "Multi < int : " << (e * f) << std::endl;
    std::cout << "Multi near 0: " << (g * g) << std::endl; 
    std::cout << "Divide > int: " << (e / g) << std::endl;
    std::cout << "Divide < int: " << (f / g) << std::endl;
    std::cout << "Divide by 0 : " << (e / 0) << std::endl;

    return 0;
}
```

#### Excercise 03 - BSP - Overload operators and basic functions

In this excercise, we must use our created Fixed class and use it for BSP - binary space partitioning to find if a point is inside a triangle defined by 3 points. 

The med-results when calculating qith Fixed values will always create some defult objects, as we overloaded the operators for this data type(class) do to it. They re created and destructed automatically ans store medium results during calculations. 

Tests:
1. Create Point by default constructor - should be (0,0)
2. Create point by overload constructor or copy constructor - should work
3. Check copy assignment operator - since x,y members are const, you cannot assign to them after the object is created - it should not be possible, should not produce compiler errors. 
4. Check the algorithm - point outside, points inside, points on corner(should be outside), points on border(should be outside), points very close to borders from inside/outside
```
int main(void)
{
    Point a(1,1);
    Point b(5,1);
    Point c(3, 3);
    Point p0(3,2);
    Point p1(0,0);
    Point p2(2,1);
    Point p3(1,1);
    Point p4(1.04, 1.003);
    Point p5(0.006,1.006);
    std::cout << std::endl;

    std::cout << "This point is inside: " << bsp(a, b, c, p0) << std::endl;
    std::cout << "This point is outside: " << bsp(a, b, c, p1) << std::endl;
    std::cout << "This point is on border: " << bsp(a, b, c, p2) << std::endl;
    std::cout << "This point is right in corner: " << bsp(a, b, c, p3) << std::endl;
    std::cout << "This point is inside very close to corner: " << bsp(a, b, c, p4) << std::endl;
    std::cout << "This point is outside very close to corner: " << bsp(a, b, c, p5) << std::endl << std::endl;

    return 0;
}
```

## CPP03 - Inheritance

#### Excercise 00 - Class implementation, member functions

In this excercise we just create a simple class with some member functions. It will be used for demonstratioon and learning in further excercises. 

Tests:
1. Check default constructors - is it there? it is needed to check constructor chaining in future excercises !
2. Check overload constructors
3. Check copy constructor
4. Check copy assignment operator
5. Check that member functions work as they should
```
int main(void)
{
    // check default constructor
    ClapTrap anonym;
    anonym.beRepaired(1);

    // check overload constructors
    ClapTrap arthur("Arthur");
    ClapTrap bob("Bob");

    // check member functions
    bob.attack("Arthur");
    bob.takeDamage(9);
    bob.takeDamage(1);
    bob.beRepaired(1); // should not work - low health
    bob.attack("Arthur"); // should not work - low health

    // check copy constuctor and copy assignmnent operator - name is the same - copied from Bob
    ClapTrap bob2(bob);
    anonym = bob;
    bob2.beRepaired(1); // should not work - copied zero health from Bob
    anonym.beRepaired(1); // should not work - copied zero health from Bob

    return 0;
}
```

#### Excercise 01 - Inheritance

Child is created using the fdefault constructor of the Base - they will not have their own name, their name is always inherited from the parent. 

Test:
1. Check default constructors - is it there? it is needed to check constructor chaining !
2. Check overload constructors
3. Check copy constructor - can you create child from base? can you create base from child? Why? (object sicing)
4. Check copy assignment operator - same as above
5. Check that child can use parent functions, and parent cannot use child-only functions
6. Check that destructor is virtual for parent - and ask why? 
```
int main(void)
{
    // check overload constructors
    ClapTrap clara("Clara");
    ScavTrap sara("Sara");

    // check basic functions
    sara.attack("Clara");
    clara.attack("Sara");
    sara.takeDamage(5);
    sara.takeDamage(4);
    sara.guardGate();
    // clara.guardGate(); // should not work, base ClapTrap does not have this function

    // test copy constructors
    ClapTrap Cat(sara);       // --> can make parent from child
    //ScavTrap Sergio(clara); // --> cannot make child from parent becasue child has something extra and object slicing would happen

    // tseting copy assignment
    ClapTrap Corgi;
    ScavTrap Sergi;
    Corgi = sara;   // --> can make parent from child
    // Sergi = clara;  // --> cannot make child from parent becasue child has something extra and object slicing would happen

    return 0;
}
```

#### Excercise 02 - Another child

The principle and excercise is just like the one before, only this child has a different method. 

Tests:
1. Most files are copied, thus only do simple checks - check that children cannot access functions of other children and that base cannot access functonis of children.

```
int main(void)
{
    ClapTrap clara("Clara");
    ScavTrap sara("Sara");
    FragTrap fred("Fred");

    fred.attack("Clara");
    sara.attack("Fred");
    clara.attack("Sara");
    fred.takeDamage(5);
    fred.takeDamage(4);

    fred.highFiveGuys();
    // fred.guardGate(); // cannot access functon of other child class
    // sara.highFiveGuys(); // cannot access function of other child class
    // clara.guardGate(); // base class cannot access function of child class
    return 0;
}
```

#### Excercise 03 - Diamond problem with inheritance

This excercise demonstrates diamond problem - when one class inherits from two separate classes with the same variables/methods. 

DiamondClap attributes and member functions will be inherited from its parent classes:
- Name, which is passed as a parameter to a constructor
- ClapTrap::name (parameter of the constructor + "_clap_name" suffix)
- Hit points (FragTrap)
- Energy points (ScavTrap)
- Attack damage (FragTrap)
- attack() (ScavTrap)

       ClapTrap
       |      |
      |        |
     |          |
    |            |
 ScavTrap     FragTrap
    |            |
     |          |
      |        |
       |      |
      DiamondTrap

Tests:
0. FragTrap and ScavTrap inherit virtually: class FragTrap : virtual public ClapTrap - What does virtual do ?  (ensures only one object exists)
1. ClapTrap sub-object has name "name"_clap_name, and the child object has name "name" - scav and frag inherit name from base, and diamond overwrites it
2. How does virtual inheritance help here? what if i remove the virtual keyword from the ClapTrap declaration ?

## CPP04 - Inheritance,, Polymorphism

#### Excercise 00 - Class Animal with 2 derived classes

Here we learn about concepts as:
- polymorphism - is is possible to treat/access/process objects of different types via the same interface (eg. assign to same class, override operators, override functions), and each type can provide its own independent implementation of this interface
- runtime polymorphism - it is possible to assign pointers of objects of derived classes to base class
- copying Animal to Cat is not be possible (unless constructor that takes in Animal is implemented)
- virtual - when using virtual and pointers/referenes to objects, it allows runtime polymorphism, and the method implementation used will be the most derived one, not the base one
- virtual functions = enable runtime polymorhism - they allow the most derived function to be used, not the one of the base object
- BUT virtual doesn't prevent slicing — it enables polymorphism, but only when you're working with pointers or references, not by value
- object slicing - when copying Cat to Animal by value, not uing references/pointers - object slicing happens - Child functions will be sliced 

Tests:
1. Test/Check Animal, Dog, Cat, WrongAnimal, WrongCat default constructor, overload constructor, copy constructor, copy assignment operator
2. Check that Animal has virtual methods and constructor - why should destructor be virtual ? 
3. !!! CHeck that in tests, the object type to which we store is of typ Animal, not of type Dog/Cat - this will definitelly work but it is not polymorphism
4. Test differences in Animal and WrongAnimal - what is the difference and why ? (WrongCat created from WrongAnimal should call the WrongAnimal sound)
```
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
```

#### Excercise 01 - Deep/shallow copies AND virtual destructors

This excercise demonstrated the difference between deep copy and shallow copy.

We can't assign one array to another as whole directly in C++ - it would create shallow copy.
Must copy the contents element by element using a loop - it creates a deep copy.
- virtual destructor in base = it must be virtual, since if it was not, the destructor of derived object that uses polymorphism would not be called, only the base destructor would be called,d and then memory leaks could occur(like Dog destructor deletes manually allocated memory on heap)

Tests:
1. Check constructors and assignment - they must allocate new brain (in  assignment, it must be deleted)
2. Destructor must delete the brain, else there will be leaks
3. Also, destructor in Animal must be virtual - what will happen if it is not? (leaks from brain - brain is allocated and freed in child constructor/destructor, but if base destructor is not virtual, it will be called, not the destructor of the derived function) 
4. Check they do not share brain - chek we create a deep copy, not a shallow copy
5. Check that the brain copy constructor and assignment copy in a loop all elements one by one
6. Check leaks
Edge cases:
5. Put empty index into getIdea
```
int main(void)
{
    int size = 4;

    // A. Checking proper destruction (virtual destructor in parent)
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

    return 0;
}
```
#### Excercise 02 - Abstract classes  ---------------------------------------------------------------------------------------------------

This excercise introduced abstract classes - classes that act as an interface, just group functionality for their derived classes but are non-instantiable. We cannot make instances of abstract classes. 

The = 0 behind a function means that this function must be re-implemented by the children, they will not be able to use the parents one. 
The ilementation can be kept though, and the class is still abstract, just provides default implementation/structure like Animal::makeSound() can be called, eg. from Dog class

Tests:
1. The name of the Animal can but des not have to be AAnimal - check folder names fit class names (but no big problem)
2. Just check that the makeSound functions is =0. What does it mean?
`Animal animal;` or `AAnimal animal;` -- this should not be possible and give error 

## CPP05 - Exceptions, Abstract classes, overriding of abstract class methods -------------------------------------------------------------------------------------------------------------------------------------------

#### Excercise 0 - Exception classes ----------------------------------------------------------------------------------------------------

Here we create our first exception class that extends std::exception.

When you create a custom exception, you usually override what() to provide a helpful error message.

When we catch base exception, all derived exceptions are also caught and they display proper messages, so we do not need to catch each error exception type seaprately, unless we want to do different actions to handle each.

Tests:
0. How are default constructors handled for bureaucrat? Create bureaucrat without arguments with default constructor
0. Check that any function implementation is in cpp file, not in header - if so, rewrite
1. Check how exceptions are implemented - they should be in bureaucrat as its member class, not in a separate file. How does it overwrite what() to get us meaningful message?
1. Test that bureaucrat throws exceptions when constructing (default, copy, copy assignment) him with bigger/smaller grade than acccepted - in copy constructors may be redundant 
2. Test that bureaucrat throws appropriate exception (same as above) when calling gradeIncrease/gradeDecrease adn it would result in grade bigger/smaller than accepted
3. Check grade increment/decrement logic -grade 1 is the highest and 150 the lowest, so incrementing a grade 3 should result in a grade 2
4. Check constructors that the grade is not assigned in the initializer list, but in the constructor body, since we first must check the logic (too high/low)
5. The main provided should include try-catch block with the exceptions 
6. Check that bureaucrat name member is const, and check how copy assignment operator handles it - test copy assignment 
```
int main(void)
{
    try
    {
      Bureaucrat a("Anna", 2);
        Bureaucrat b("Bob", 1);
        Bureaucrat c("Clara", 149);
        Bureaucrat anonym;
        // Bureaucrat d("Daria", 160); // throws GradeTooLowException
        std::cout << std::endl;

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << anonym << std::endl;
        std::cout << std::endl;

        // testing member function logic 
        a.incrementGrade();
        // b.incrementGrade(); // throws GradeTooHighException
        c.decrementGrade();
        //c.decrementGrade(); // throws GradeTooLowException

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << c << std::endl;
        std::cout << std::endl;    

        // testing copy constructor
        Bureaucrat e(b); // was initialized to 1 by copying
        std::cout << e << std::endl << std::endl;

        // testing copy assignment operator
        Bureaucrat f("Frank", 10);
        std::cout << f << std::endl;
        f = e; // error - cannot assign object that has const members OR some other way to handle this 
        std::cout << f << std::endl << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```

#### Excercise 1 - Circular dependencies  -----------------------------------------------------------------------------------------------

Tests:
0. How are default constructors handled for forms? Which values are used for forms? Try to create Form without arguments with default constructor 
1. Check circular dependencies and how they are handled  - between which object it exists (Form, Bureaucrat)
2. Circular can afect also the GradeTooHighException/GradeTooLowException, since both classes Bureaucrat and Form implement them - same namespaces ! - make sure they print proper messages abou form/bureaucrat and when called, proper namespace is used - that is relevant !
2. AND check that every class includes the <exception> header, since the class files must be usable on their own 
2. Check how grade is checked for too high/too low when constructing form
3. Form attributes are private, not protected
4. Check how signForm checks for too low grade for signing
5. Check how Form::beSined and Bureaucrat::signForm interact - first should check grade and throw exception, second should try-catch the first one and have proper messages in the block
6. Try to sign a signed form
```
int main(void)
{
    try
    {
        Bureaucrat a("Anna", 20);
        Bureaucrat b("Bob", 20);
        Form c("Work Contract", 20, 10);
        Form d("Car Contract", 20, 10);
        std::cout << std::endl;

        std::cout << b << std::endl;
        b.signForm(c); // works - Bob has access
        std::cout << c << std::endl << std::endl;
    
        b.decrementGrade();
        std::cout << b << std::endl;
        b.signForm(d); // does not work - Bob has not access anymore
        std::cout << d << std::endl << std::endl;
    
        std::cout << a << std::endl;
        a.signForm(d); // works - Anna has enough access
        std::cout << d << std::endl << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```
#### Excercise 2 - Overriden Forms inheriting from abstract class AForm -----------------------------------------------------------------

Making an abstract class and making 3 classes that inherit from it. Must raise appropriate exceptions.

Here we learn that 

Tests:
1. Creating Bureaucrat object with too low/high grade (other than range 1-150)
2. Bureaucrat trying to sign/execute form with not enough high grade
3. Trying to execute unsigned form
4. Check that AForm attributes are private, not protected
5. Check if execute is pure virtual function ( = 0 )
6. Check all 3 form types and their functions
7. ShrubberyForm - if file cannot be opened(chmod a-w...)
7. RobotomyForm - check how form is signed 50% of the time - what is used ? 
8. Test executing form that is not signed
9. Test signing form that bureaucrat does not have permission to sign
10. Test if we can create by copy constructor a form of one type from form of another type - try to copy a SIGNED form to see if the isSigned variable is going to be copied ! 
11. Can test for empty input in target field when constructing form types but it is not what the excercise is about 
12. Execute ShrubberyForm multiple times - is the Garden(or other name) file still correct ? 

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

#### Excercise 3 - Function pointers again  ---------------------------------------------------------------------------------------------

This excercise is about creating a small but more extensive program where multiple classes interact. 

Tests:
1. Check how the makeForm is creating different forms - cannot have many if statements
2. Forms are created with new, since they return teh pointer, check with valgrind.
3. Test creation of all 3 forms by the intern.
4. Test all 3 forms being usable by bureaucrats - try to sign and execute.
5. Check how intern implementes the makeForm function
6. Test creating a form that does not exist AND then print it with << - segfault ? 

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

## CPP06 - Casting

#### Excercise 0 - Static cast between known data types at compile time - unsafe, must check overflow etc. before

This excercise taught us to safely cast among the primitive data types and between string and primitive data types. 

I choose static cast, because it is used for casting of one type to another at compile time, and since we know which data types we are casting to, it is a logical choice.
However static_cast is unsafe, meaning it does not handle runtime errors like overflow, underflow, or invalid conversions. It simply performs the conversion you tell it to. So it is your job to check if teh cast is safe by manually checking the range before casting.

Steps:
1. First, I have functions to figure out which data type is represented by the input string literal - char/int/float/double based on specifiers like ., f.
2. After figuring out which type I received, I use string streams to read from the input literal string into that data type, which results in iss.fail() or !iss.eof() if there is problem in reading the string into the selected data type.
3. Last;y I have function for each data type to handle explicit casting to the other 3 types, handling also pseudo-literals, and printing it to stdout.
4. If in any case an error happens - invalid argument, overflow error, excape sequence does not exist, etc. is handled via exceptions.

The subject sayst we cannot be able to instantiaate the class, which can be done by making the constructor private. But DID YOU KNOW that even if we make the constructor private, it is still able to be instantiated by calling the constructor in its static member method and returning it? Then, calling this static method from outside of the class and assigning it to object of this class will make an instance of it and make it accessible to outside (but in c++98 we would also have to implement the copy constructor). HOWEVER, the subject it cannot e instantiable by user, it does not say it cannot be instantiable by the class methods. 

Except for char parameters, only the decimal notation will be used - so no scientific notation etc. We had to think of many possible error situations.

I CREATED A TESTER THAT CHECKS ALL POSSIBLE CASES - CORRECT AND INCORRECT THAT SHOJLD BE HANDLED. THE OUTPUT IS WRITTEN TO cpp06-ex00_results.txt FILE. NEEDS TO BE CHECKED MANUALLY ( USE YOUR VISUAL AND LOGICAL ABILITIES :) CHANGE PATH TO EXECUTABLE ACCRDING TO YOUR PROJECT. HOWEVER, THE IMMPLEMENTATION OF EACH STUDENT CAN VARY, ESPECIALLY FOR HOW YOU CHECK FOR NAN,NANF... OR IF YOU INCLUDE '' FOR CHARS IN THE INPUT AND REMOVE IT FOR PROCESSING OR NOT OR IF SINGLE DIGITS ARE REPRESENTED AS CHAR OR INT. THUS IT IS JUST A TOOL FOR DISCUTTION, AND IS NOT GROUNDS FOR FAILING SOMEONE NOR AUTOMATIC SUCCESS. IF SOMETHING DOESN'T SEEM RIGHT, RUN THE PROGRAM WITH THAT ARGUMENT. 

Tests:

A. wrong input - does not match any types string literal
1. af
2. 0.4ff
3. f
3. --0.222
4. 1.f - float ending with .
5. 1. - double ending with .
6. '' - empty string
7. .f 
8. 1f - not valid string literal in cpp but can possibly handle it
9. 8 - check if it takes it as int or char 
10. no input, more than 1 input
11. '\j' - invalid escape sequence
12. hello - not known string literal

B. should print
11. '\''
12. - 

-  prints but char is non-displayable:
13. '1'
14. -1
15. '\n'
16. 0
17. -0
18. +0
19. 298 - checks if wrapping is handled - if not, prints * (char is max 255, so if it receives higher number, it will wrap - %256 - should it/ shuld it not ?)

- pseudo-literals: char and int are impossible - when testing this, check that they print it as a converted type, not printing the string !
21. nan
22. +inf
23. -inf
24. nanf
25. +inff
26. -inff

- out of range during static_cast
30. 2147483649.0f - float cannot cast to int - impossible (overflow)
31. 2140000000000000000000000000000000000000000000000.0 - double cannot cast to float/int - impossible (overflow)

C. should trigger error/exception
36. 2147483649 - < max int
37. 100000000000000000000000000000000000000000000000.0f - < max float
38. max double can hardly be tested since it is ~1.8 × 10^308

#### Excercise 1 - Reinterpret cast - Casting between uneralted data types

This excercise taught us how to work with reinterpret casting. 
- reinterpret_cast = used for low-level casting between unrelated types like pointers and integers
- uintptr_t = unsigned integer type that can safely hold a pointer

The deserialized pointer must equal the pointer from which it was serialized.

Tests:
1. Create pointers
2. Populated and valid Data pointers
3. Compare the variables storing initial and serialized+deserialized pointer - must be the same
4. NULL pointer passed to serialize
5. 0 passed to deserialize
6. valgrind !

```
int main()
{
    int size = 10;
    Data* a[size];
    
    int i = 0;
    while (i < size)
    {
        a[i] = new Data();
        a[i]->value = i;
        i++;
    }
    a[size] = NULL;

    i = 0;
    while (i < 11)
    {
        try
        {
            uintptr_t b = Serializer::serialize(a[i]);
            std::cout << "Serialized: " << b << std::endl;
    
            Data* c = Serializer::deserialize(b);
            std::cout << "Deserialized: " << c->value << std::endl;
    
            // the deserialized pointer must equal the pointer from which it was serialized
            std::cout << static_cast<void*>(c) << " ?= " << static_cast<void*>(a[i]) << std::endl; // static cast to void pointer to ensure it is printed sa pointer
            if (c == a[i])
                std::cout << "The pointer is the same after serialization and deserialization." << std::endl;
            else
                std::cout << "The pointer is differenet after serialization and deserialization." << std::endl;
        }
        catch (std::runtime_error e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        catch (std::invalid_argument e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        i++;
    }
    // testing deserialize
    try
    {
        Data* c = Serializer::deserialize(0);
        std::cout << "Deserialized: " << c->value << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    delete a[size];
    return 0;
}
```

#### Excercise 02 - Dynamic casts - using them at pointers/references that use polymorphism to identify the data type

Dynamic cast only works with polymorphic types (that at least one virtual function) and only on pointers/references. 

This excercise shows us difference between dynamic casts to pointers and to references.
- dynamic cast to pointer = it’s non-throwing, so no try-catch is needed, if fails, returns nullptr - you can check each cast afterwards with if (ptr) safely, works even if the pointer is nullptr
- dynamic cast to reference = cast fails if type is not correct and throws std::bad_cast exception, so must wrap it in a try-catch block and if checking for multiple types, check the rest in this block, reference must be non-null, so we do not have to check for nullptr because it will never happen
- ( result of the cast is cast to void - must be there because we have to do some operation with the casted deference to possibly trigger an exception, and it cannot be it (ref), cause that is illegal, and it cannot be assigned ot variable, since we will not use it and will get unused variable error )

Tests:
1. try to cast other class into identify
2. test idenfity with pointer with nullptr
```
int main()
{
    int count = 3;
    int     i = 0;

    while (++i <= count)
    {
        Base *b;
        if (i < count)
            b = generate();
        else
            b = nullptr;
        std::cout << "Identifying via pointer: ";
        identify(b);
        std::cout << "Identifying via reference: ";
        identify(&(*b));

        delete b;
    }
    return 0;
}
```

## CPP07 - STL

#### Excercise 0 - Function templates

This excercise introduces function templates. What is important to know is to always define (declare+implement) it in header file, because compiler must see the definition then it instantiates the function with the type it received. 

Pass in references or pointers where possible to avoid copying large objects. 

```
template <typename T, U>
T functionName(T& x, U& y) {}
```

Test (from subject):
```
int main( void )
{ 
    int a = 2;
    int b = 3;
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::cout << std::endl;

    std::string c = "apple";
    std::string d = "banana";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    std::cout << std::endl;

    float e = 1.123f;
    float f = 0.55f;
    ::swap(e, f);
    std::cout << "e = " << e << ", f = " << f << std::endl;
    std::cout << "min( e, f ) = " << ::min( e, f ) << std::endl;
    std::cout << "max( e, f ) = " << ::max( e, f ) << std::endl;
    std::cout << std::endl;

    char g = '*';
    char h = '?';
    ::swap(g, h);
    std::cout << "g = " << g << ", h = " << h << std::endl;
    std::cout << "min( g, h ) = " << ::min( g, h ) << std::endl;
    std::cout << "max( g, h ) = " << ::max( g, h ) << std::endl;
    std::cout << std::endl;


    return 0;
}
```

#### Excercise 01 - Function pointer as parameter to function template

This excercise teaches about passing function pointers and even function templates as a function template parameteres. 

You can pass a function pointer that takes in only one specific data type, however you can then only pass in arguments of that data type, else it gives an error. But if i input a function taking just one data type to a function template, it will only take argument of that type. 

Also explored passing in const variables. To support both const and non-const arguments in function templates, function template must be overloaded to accept const data type.

My test cases and simple test functions test for non-cons and const functions and function templates passed as third argument, check edge cases, and the commented calls should result in runtime/compilation errors. 

Test main:
```
// some functions
// a. non-const
void add_one(int& x)
{
    x += 1;
}

// b. const
void print_int_arr(const int& x)
{
    std::cout << x << ", ";
}

// some template functions for testing
// a. non-const
template <typename T>
void add(T& el1)
{
    T temp = el1 + el1;
    el1 = temp;
}

// b. const 
template <typename I>
void print_arr_el(const I& el)
{
    std::cout << el << ", ";
}

int main( void )
{
    int size = 7;

    // some arrays of different types 
    int int_arr[] = { 1, 2, 3, 4, 5 };
    const int const_int_arr[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    char char_arr[] = { '!', '"', '#', '$', '%' };
    const char const_char_arr[] = { '^', '&', '*', '(', ')' };
    std::string str_arr[] = { "Dog", "Cat", "Cow", "Mouse", "Tiger" };
    const std::string const_str_arr[] = { "Giraffe", "Monkey", "Bug", "Elephant", "Wolf" };

    // passing in functions
    ::iter(int_arr, sizeof(int_arr) / sizeof(int_arr[0]), add_one); // --> works - int arr, int function
    ::iter(int_arr, sizeof(int_arr) / sizeof(int_arr[0]), print_int_arr); // --> works - int arr, const int function
    //::iter(char_arr, size, add_one); // --> does not work - char arr, int function
    std::cout << std::endl << std::endl;
    
    // passing in template functions:
    ::iter(char_arr, sizeof(char_arr) / sizeof(char_arr[0]), add); // --> works - non-const char arr, non-const template function
    ::iter(char_arr, sizeof(char_arr) / sizeof(char_arr[0]), print_arr_el); // --> works - non-const char arr, const template function
    // ::iter(char_arr, size, add_one); // --> does not work - char array, int function
    std::cout << std::endl;
    //::iter(const_char_arr, size, add); // --> does not work - const char arr, non-const template function that tries to modify the array
    ::iter(const_char_arr, sizeof(const_char_arr) / sizeof(const_char_arr[0]), print_arr_el); // --> works - const char arr, const template function
    std::cout << std::endl << std::endl;

    ::iter(int_arr, sizeof(int_arr) / sizeof(int_arr[0]), add); // --> works - int arr, non-const template function
    ::iter(int_arr, sizeof(int_arr) / sizeof(int_arr[0]), print_arr_el); // --> works - int arr, const template function
    //::iter(const_int_arr, size, add); // --> does not work - const array, non-const template function add tries to modify the array
    std::cout << std::endl;
    ::iter(const_int_arr, sizeof(const_int_arr) / sizeof(const_int_arr[0]), print_arr_el); // --> works - const array, const template function
    std::cout << std::endl << std::endl;

    ::iter(str_arr, sizeof(str_arr) / sizeof(str_arr[0]), add); // --> works - int arr, template function
    ::iter(str_arr, sizeof(str_arr) / sizeof(str_arr[0]), print_arr_el); // --> works  - string arr, template function
    //::iter(const_str_arr, size, add); // --> does not work - const array, non-const template function add tries to modify the array
    std::cout << std::endl;
    ::iter(const_str_arr, sizeof(const_str_arr) / sizeof(const_str_arr[0]), print_arr_el); // --> works - const string array, const template function
    std::cout << std::endl << std::endl;

    // edge cases tests
    ::iter<int>(NULL, size, print_int_arr); // should safely do nothing
    ::iter(int_arr, 0, print_int_arr); // empty array, prints nothing
    ::iter(int_arr, -1, print_int_arr); // egative length, does not run

    return 0;
}
```

#### Excercise 02 - Class templates

This excercise aims to teach us about class templates. They are a way to avoid duplicit code, for example so the code for class for int arrays and class for string array and class for char arrays to be grouped together. 

Templates definitions are stored in the .hpp files, and templates implementations are stored in .tpp files. TPP files are included at the END of hpp file, and implementation of any function in tpp must have the template <typename T> in front of itself.  

Can template function of one type be used with copy constructor/copy assignment operator with object if that template with another type ?

Create object of class template as Array<int> IntArray; Array<std::string> StringArray; ...

Tests:
1. check with valgrind when there is destructor AND copy assignment operator - they must delete the created array, else there WILL be leaks 
2. check that the array created with default constructor exists but its empty and that the size is initialized
3. check that the array created with overload constructor is value-initialized with default values for their data type - there is () after new T[n]() in overload constructor!
4. check that the array created with copy asssignment creates deep copy - change newArr[0] to something else and then check values in both newArr[0] and oldArr[0] - should be different
5. do the same for copy assignment
6. do assignment from array that has size 0, check valgrind and print the [0] value
7. copy the same element with copy assignment operator - should not do anything - check the values 
8. test the size() function on empty and non-empty array
9. test out of bounds access - should throw exception
```
int main( void )
{
    int size = 5;

    try
    {
        // 1. empty array with default constructor - should have size 0 and _array initialized to NULL
        Array<int> emptyArr;
        std::cout << "Empty array size: " << emptyArr.size() << std::endl;
        try
        {
            std::cout << "Empty array[0]: " << emptyArr[0] << std::endl; // should throw out of bounds exception
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;

        // 2. int array created with overload constructor - should have size n and values are initialized to default value of provided data type
        Array<int> intArr(size);
        std::cout << "Int array size: " << intArr.size() << std::endl;
        for (unsigned int i = 0; i < intArr.size(); ++i)
            std::cout << intArr[i] << ", ";
        std::cout << std::endl;
        try
        {
            std::cout << "intArray[7]: " <<  intArr[7] << std::endl; // should throw out of bounds exception
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;

        // 3. string array created with overload constructor - must be value-initialized
        Array<std::string> strArr(size);
        std::cout << "String array size: " << strArr.size() << std::endl;
        for (unsigned int i = 0; i < strArr.size(); ++i)
            std::cout << strArr[i] << ", ";
        std::cout << std::endl;
        // testing changing element values with []
        strArr[0] = "Dog";
        strArr[1] = "Cat";
        for (unsigned int i = 0; i < strArr.size(); ++i)
            std::cout << strArr[i] << ", ";
        std::cout << std::endl << std::endl;

        // 4. test copy constructor - should create deep copy
        //Array<char> charArr(strArr); // does not work - not allowed - trying to construct from different type
        Array<std::string> copyStrArr(strArr);
        std::cout << "Other string array size: " << copyStrArr.size() << std::endl;
        for (unsigned int i = 0; i < copyStrArr.size(); ++i)
            std::cout << copyStrArr[i] << ", ";
        std::cout << std::endl;
        // testing if deep copy was created
        copyStrArr[0] = "Mouse";
        std::cout << "strArr[0]: " << strArr[0] << ", copyStrArr[0]: " << copyStrArr[0] <<" => should be different!" << std::endl << std::endl;

        // 5. const string array - works as others, but does not allow a[10] = ...
        const Array<std::string> constStrArr(strArr);
        std::cout << std::endl;
        //constStrArr[0] = "Cow"; // does not work - not allowed - trying to reassign const element

        // 6. testing copy assignment operator for size 0 - Empty Array
        Array<int> newIntArr(5);
        std::cout << "New Int array size: " << newIntArr.size() << std::endl;
        newIntArr = emptyArr;
        std::cout << "New Int array size: " << newIntArr.size() << std::endl;
        try
        {
            std::cout << "newIntArr[0]: " << newIntArr[0] << std::endl; // should raise exception since we copied it from an empty array
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << std::endl;
        
        // 7. testing copy assignment operator creates a deep copy -- check there are no leaks !
        intArr[0] = 42;
        newIntArr = intArr;
        std::cout << "New Int array size: " << newIntArr.size() << std::endl;
        for (unsigned int i = 0; i < newIntArr.size(); ++i)
            std::cout << newIntArr[i] << ", ";
        std::cout << std::endl;
        newIntArr[0] = 43;
        std::cout << "newIntArr[0]: " << newIntArr[0] << ", intArr[0]: " << intArr[0] <<" => should be different!" << std::endl;
        std::cout << std::endl;

        // 8. testing copying the same element with copy assignment operator --> should do nothing AND no leaks
        // intArr = intArr;
        // std::cout << "Int array size: " << intArr.size() << std::endl << std::endl;
        // for (unsigned int i = 0; i < intArr.size(); ++i)
        //     std::cout << intArr[i] << ", ";
        // std::cout << std::endl << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

## CPP08 - STL, Containers, Algorithms

#### Excercise 00 - Containers and iterators

This excercise teached us about iterators and STL algorithms. 

Iterators are objects like pointers used to iterate over containers - always point to some element of the container. The begin() and end() member functions of the containers can be used to set the initial position and the iterators can be operated on with + and- operators like normal pointers. 

STL algorithms are functions that operate on containers using iterators.

Tests:
0. Check STL is used - algorithm functoins, iterators, not C syntax 
1. Check if it works with const containers (the function easyfind is overloaded with const_iterator), and also a const_iterator must be returned
2. Check what it returns - if it returns iterator or value, and ask what si the difference
3. Check various containers - vector, list, deque (not associative)
4. Check values in container and not in container
5. Check duplicate values
```
int main()
{
    // vector
    int arr1[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr1, arr1 + 5);

    // list
    int arr2[] = { 100, 200, 300 };
    const std::list<int> lst(arr2, arr2 + 3);

    // vector
    int arr3[] = { 1, 2, 2, 2, 2};
    std::vector<int> duplicates(arr3, arr3 + 5);

    // empty
    int arr4[] = {};
    std::deque<int> empty(arr4, arr4);

    // deque
    int arr5[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::deque<int> deque(arr5, arr5 + 9);

    try
    {
        std::vector<int>::iterator it1 = easyfind(vec, 1); // element exists
        std::cout << "Found in vector: " << *it1 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::vector<int>::iterator it2 = easyfind(vec, 10); // element does not exist
        std::cout << "Found in vector: " << *it2 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
        std::list<int>::const_iterator it3 = easyfind(lst, 300);  // element exists - const container
        std::cout << "Found in list: " << *it3 << std::endl;
    try
    {
        std::vector<int>::const_iterator it4 = easyfind(duplicates, 2);  // duplicate elements - gets the first occurence
        std::cout << "Found in list: " << *it4 << " on index: " << it4 - duplicates.begin() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::deque<int>::const_iterator it5 = easyfind(empty, 1);  // empty container - element is not found
        std::cout << "Found in list: " << *it5 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    try
    {
        std::deque<int>::iterator it6 = easyfind(deque, 0); // outside of container
        std::cout << "Found in deque: " << *it6 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```

#### Excercise 01 - Container functions 

I gathered this excercise is about using the STL functions that can operate on containers.

Tests:
1. default constructor - initializes empty array
2. overload constructor and copy constructor work properly
4. copy assignment operator - does not work if there is a const member, which size should be !! - if size is not const, can be changed to something smaller than current container size --> logical error
5. adding numbers to full array --> exception
6. minSpan / maxSpan if number of elementes is < 2 --> exception
7. minSpan / maxSpan if maxEl and minEl are the same - works
8. adding a range(iterators from other containers) - add more numbers so size would be exceeded
10. adding a range(iterators from other containers) - add from container of different type
11. adding a range(iterators from other containers) - add from a const container - the iterator will be different - so the function to add multiple numbres must be a template
12. initialize Span with negative size, try to populate and show min/max spans - has to be 0 to 4294967295
13. Span with over 10,000 numbers
```
int main( void )
{
    try
    {
        // default constructor - initialize empty span with size 0 and initialized container
        Span emptySpan;
        std::cout << "Limit: " << emptySpan.getMaxSize() << " - current: " << emptySpan.getRealSize() << std::endl;

        // overload and copy constructor
        Span span(20000);
        Span copiedSpan(span);

        // copy assignment operator - size should be const, and it should not work - cause if size is not const, it can be set to smaller number than current number of elements
        // Span newSpan;
        // newSpan = span;
        
        // populating the container - loop fills it fully, next one raises exception
        for (unsigned int i = 1; i <= copiedSpan.getMaxSize(); i++)
            copiedSpan.addNumber(i);
        // copiedSpan.addNumber(10);
        std::cout << "Limit: " << copiedSpan.getMaxSize() << " - current: " << copiedSpan.getRealSize() << std::endl;
        
        // adding range of numbers from a list
        int arr2[] = { 100, 200, 300 };
        const std::list<int> lst(arr2, arr2 + 3);
        span.addNumbers(lst.begin(), lst.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // adding range of numbers from a CONST vector
        const std::vector<int> duplicates(10, 1);
        span.addNumbers(duplicates.begin(), duplicates.end());
        std::cout << "Limit: " << span.getMaxSize() << " - current: " << span.getRealSize() << std::endl;

        // checking max and min spans
        std::cout << "Max: " << span.longestSpan() << " , min: " << span.shortestSpan() << std::endl;

        // checking max and min spans if the numbers are the same
        Span s(10);
        for (unsigned int i = 1; i <= 10; i++)
            s.addNumber(10);
        std::cout << "Max: " << s.longestSpan() << " , min: " << s.shortestSpan() << std::endl;

        // checking max and min span if there are less than 2 elements - raises exception
        Span s1(1);
        s1.addNumber(10);
        // std::cout << "Max: " << s1.longestSpan() << std::endl;
        // std::cout << "Min: " << s1.shortestSpan() << std::endl;

        // adding range so that size is exceeded
        Span s2(10);
        for (unsigned int i = 1; i <= 10; i++)
            s2.addNumber(10);
        s2.addNumbers(duplicates.begin(), duplicates.end());
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

#### Excercise 02 - Container adapters - stack

In this excercises, we explore the Stack container type, which is not iterable, LIFO structure, and implement out own Stack class, which is based on the stack and offers the stack functions, but also allows iteration. 

Not all containers support same operations or operators or iterators !!! 

Reference: https://cplusplus.com/reference/stack/stack/

So this is the template: it receives one member T, which is type of the elements, and optional second element Container type, which is the type of container used, default is deque.
The class then inherits from stack, passing the same template parameters to stack when it is created
```
template <class T, class Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
```

Tests:
0. Test default construction with only int type, no container type - it should be deque: `MutantStack<int> stack1;`
1. Test construction with different container types: `MutantStack<int, std::vector<int> > vectorStack;`
2. Create const container - ask how they would create it (cannot push/pop, only from copy/assignment)
3. Test basic stack operations (push, pop, empty, size, ...)
4. Test copy constructor and copy assignment operator and check they have the same elements as what they were created from
5. Test iterator, reverse iterator - ask how they would print the element on which the iterator is
6. Test const iterator, reverse const iterator
7. test mutantStack<int, std::list<int> > and try to print *(++stack1.begin()) vs. *(stack1.begin() + 4) --> why does the latter not work ?
```
int main(void)
{
    // testing construction with default container type - should be deque
    MutantStack<int> stack1;   
    MutantStack<int> stack2; 

    // testing basic stack operations
    for (int i = 1; i <= 10; i++)
        stack1.push(i);
    stack1.pop();
    std::cout << "Stack1: " << stack1.size() << ", empty: " << stack1.empty() << std::endl;

    // testing construction with other container type - vector, list, ...
    MutantStack<int, std::vector<int> > vectorStack;  
    std::cout << "VectorStack: " << vectorStack.size() << ", empty: " << vectorStack.empty() << std::endl;

    // testing copy constructor
    MutantStack<int> copyStack(stack1);
    std::cout << "CopyStack: " << copyStack.size() << ", empty: " << copyStack.empty() << std::endl;

    // testing copy assignment operator
    stack2 = stack1;
    // vectorStack = stack1; // should not work - different types - vector vs deque

    // testing const stack and basic operations
    const MutantStack<int> constStack(stack1);
    std::cout << "ConstStack: " << constStack.size() << ", empty: " << constStack.empty() << std::endl << std::endl;

    // testing the basic iterator
    std::cout << "Begin: " << *(stack1.begin()) << ", end: " << *(--stack1.end()) << std::endl;

    // testing the reverse iterator
    std::cout << "Reverse begin: " << *(stack1.rbegin()) << ", reverse end: " << *(--stack1.rend()) << std::endl;

    // testing the const iterator
    std::cout << "Const Begin: " << *(constStack.begin()) << ", const end: " << *(--constStack.end()) << std::endl;

    // testing the const reverse iterator
    std::cout << "Const reverse begin: " << *(constStack.rbegin()) << ", const reverse end: " << *(--constStack.rend()) << std::endl;

    return 0;
}
```

## CPP09 - STL

#### Excercise 00 - Bitcoin Exchange (maps)

I use the map container here to store Date objets as keys and doubles as values: std::map map<Date, double>

The files can have first line representing column names but do not have to, work also when starting with dates right away.



Tests:
0. Basic checks
aa. All tests that end in error and end program execution should end with 1 error code (or other non-0)
a. Provided database (data.csv or other, defined in program) does not exist or no read permission
b. Database provided in argument does not exist or no read permission
c. Provided file is empty
d. Argument file is empty
e. Wrong number of arguments
f. check if it works both if column names are on first line and when are not

1. Check both files for valid date and how thoroughly invalid dates are checked
aa. correct date 
a. day < 0
b. day = 0
c. month < 0
d. month = 0
c. year < 0
d. day > 31
e. month  > 12
f. month that doesn't have 31 days: 2025-04-31
g. february has only 28 days: 2025-02-28
h. leap year is allowed: 2024-02-29
h. any value more than max int
g. any value value less than min int 
2. Change the provided input file with prices to have wrong fields
a. value missing
b. wrong date 
c. wrong date format - eg. 202-12-12
c. wrong format
d. extra characters after the value
e. negative value
f. value more than max int
g. value less than min int 
h. ipnut float as value
h. duplicate dates - check how duplicates are handled (override the old one/ignore the new one/ abort and quit program ?)
3. Change the input file with the ammounts to have wrong fields
aa. correct date
a. value missing
b. wrong date 
c. wrong format
d. extra characters after the value
e. negative value
f. value more than max int
g. value less than min int 
h. input float as value
h. duplicate dates - allowed 
i. Date not container in the provided db - must use the lower one
j. Date does not exist but there is no lower date
k. Value is > 1000
l. Date in future ? not error

Tests for the date:
2025-01-31 | 1.1
2025-01-31 | 1.1 // duplicate
2025-02-31 | 1.1
2025-03-31 | 1.1
2025-04-31 | 1.1
2025-05-31 | 1.1
2025-06-31 | 1.1
2025-07-31 | 1.1
2025-08-31 | 1.1
2025-09-31 | 1.1
2025-10-31 | 1.1
2025-11-31 | 1.1
2025-12-31 | 1.1
2024-02-0 | 1.1
2024-02--2 | 1.1
2024-03-32 | 1.1
2024-0-01 | 1.1
2024--1-01 | 1.1
2024-13-01 | 1.1
-1-12-01 | 1.1
2011-02-28 | 1.1
2011-02-29 | 1.1
2024-02-29 | 1.1
2024-02-30 | 1.1
209876543234567-01-01 | 1.1
2025-04-01 | -1
2025-04-01 | 0
2025-04-01 | 1000
2025-04-01 | 1001

#### Excercise 01 - Reverse polish notation

Reverse polish notation is another way of writing mathematical operations - the sign is not in the middle, but after both operands. 

Logically I implement it as  stack, taking elements from top one by one, starting with the sign to know which operation to do and then taking first and second operand. 

HOW IT WORKS: when reading the expression, the numbers are added to the stack, and as soon as operator is encounterd the 2 stored numbers are taken out and the operation is performed on them and pushed to stack. Then te next operand is pushed to stack. 

Simple explanation on stacks in python:
https://medium.com/@danish9980/solving-arithmetic-expressions-with-reverse-polish-notation-rpn-in-python-59c8aeec12a6

THERE IS A TESTER FOR THIS EXCERCISE IN testers/ RUNNING THE PRIGRAM WITH VARIOUS CORRECT AND WRONG EXPRESSIONS, CHECKING CORRECTNESS OF THE OUTPUT, WRONG FORMAT HANDLING, INT OVERFLOW HANDLING, WRONG ARGUMENTS, ETC. IT OUTPUTS A RESULTS FILE WITH TEST CASE, EXPECED OUTPUT, AND PROGRAM OUTPUT. IT IS UP TO THE EVALUATOR TO CHECK IF THE PROGRAM OUTPUT MATCHES EXPECTED RESULT AND TO CHECK THAT ERRORS ARE PROPERLY HANDLED. HOWEVER, THIS IS MERELY A TOOL FOR DISCUSSION ADN AUTOMATION OF MANUAL WORK, AND ITSELF IT SHOULD NOT BE THE BASIS FOR EVALUATION RESULT. THE EVALUATOR SHOULD PERFORM THEIR OWN TESTS IF THE RESULT SEEMS NOT CORRECT, AND DISCUSS WITH THE EVALUATEE WHY THEY CHOSE THAT HANDLING.

Errors:
1 + 
1 2 3 +
1 2 a
a 2 +
+ 1 2
1 3 + 9 + 4 2 + - = 7
10 10 * 10 * 10 * 10 * 10 * 10 * 10 * 10 * 10 *
Check for invalid arguments
Check for invalid formats (missing/extra opertors etc.)
Check for overflow error: 10 10 * 10 * 10 * 10 * 10 * 10 * 10 * 10 * 10 *
Check for wrong number of arguments
Division by 0

#### Excercise 02 - Merge insertion (Ford-Johnson algorithm) using 2 different container types

The task is to implement this algorithm for 2 different container types (advised not to do a generic function) and compare how much time it takes for both. 

Evaluation constraints:
As an evaluator, you need to follow the scale, meaning that, the `proper algorithm, **Ford-Johnson**, **is used**` and the `proper sequence, **Jacobsthal** **numbers**, **as well**` . As the scale says, an explanation of these concepts is expected:
> Check in the code that the merge-insert sort algorithm is present and is used for each container. The Ford-Johnson algorithm must be used.
Therefore, the student must be capable of explaining the following concepts:
> The key aspects of merge insertion, specifically the role of pairs.
> The Jacobsthal sequence and its relevance.
> The process of binary search.
> A brief explanation is expected. In case of doubt, the evaluation stops here.

Concepts:
- Ford-Johnson Algorithm = it is a sorting algorithm, and although it is not the fastest nor the most optimal, it was for a long time the algorithm that took the least numbers of comparisons. 
- Jacobsthal numbers = integer sequence like related Fibonacci numbers that starts with 0 and 1, then each following number is found by adding the number before it to twice the number before that - the first Jacobsthal numbers are 0, 1, 1, 3, 5, 11, 21, 43, 85, 171 - they fulfill the recursive Lucas sequence in which xn = (P * xn-1) - (Q * xn-2) --> for Jacobsthal numbers, P = 1, Q = -2
- binary search = searching algorithm that operates on sorted sequence, repeatedly dividing it into halves to find a target - has logarithmic time O(log N)
- binary insertion = we use binary search to find the location where an element should be inserted - reduces number of comparisons for inserting a single element from O (N) to O (log N)
- 

It is often confused with the merge sort algorithm. 

The Wikipedia page and the corespnding graph seem to underestimate the recursive step of pairing and sorting pairs of numbers, pairs of airs of numbers, pairs of pairs of pairs of numbers ... etc.

Steps of the algorithm as I understand them:
A. SPLITTING
1. make adjacent elementes into pairs, if the number of elementes is odd, keep the last one separate
2. sort these pairs - here and for the future operations, the bigger element is refered to as a, the smaller as b, each marked with the number of the pair in the sequence - a1 > b1, a2 > b2, a3 > b3, ...
3. when the pairs of  numberes are sorted, move to next "level" where you operate on pair of pairs of numbers - first pair of 2 numbers is L1(size 2), the next pair of pairs of numbers is L2(size 4 - 2 + 2), the next pair of pairs of pairs of numebrs is L3(size 8), etc. With each level the size of the "box" wrapping a pair grows by powers of 2. Each level has its a and b element, which is always the last element of each pair 
3. when each pair is sorted, use recursion for step 2 - again make pairs - but now one level higher - pairs of pairs, and sort them based on the bigger element in each pair (a)
4. recursively repeat step 2 until there are 2 last pairs, and they get sorted - always compare on the largest element of pair (it should always be the last one). !!! when switching pairs, always change the whole pairs, not only 2 elements - eg if each pair has 2 pairs on lower level, always change the whole "box", not changing the order within them anymore
5. --> so the comparison always happens on teh largest(last) element of the pair, but the swapping occurs on the whole sequence
6. odd size - if a number/pair("box") does not have a pair, we simply leave it at the end (since we start forming the pairs from the beginning, if there is any leftover number/pair, it will always be at the end)
7. if the box does not have a pair becasue a box of the same size cannot be created from the leftover elements/boxed, just leave them at the end
B. MERGING
1. we start from the highest level - the largest box that encompasses smaller pairs, possible leftovers are at the end, not considered yet. As mentioned before, each pair has its a and b element where a > b.
2. we start the final sequence with 

https://en.wikipedia.org/wiki/Merge-insertion_sort
https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91 - however this is WRONG - it suggests making recursive pairs and pairs of pairs etc and always sorting tese based on teh biggest element, but it is not correct acording to the description in The Art of Computer Algorithms by Knuth!

Forming pairs:
So i always have at most a pair of large-small ints, never pair of large Pair - small Pair ? I always create new pairs on each level of recursion from main?

Extra(odd) elements:
If at one recursion level you have an odd number of elements, the extra element automatically goes into the main chain. On the next recursion level, that element is now part of the new main chain and it can be paired with an adjacent element from this new main chain. Then it participates normally in winner/loser classification at that level.

0. initial container - is container oof ints, not container of pairs:
18 15 4 6 12 1 21 10 19 17 5 14 2 8 3 20 16 11 13 7 9 

1. form pairs of adjacenet ints
(18 15) (4 6) (12 1) (21 10) (19 17) (5 14) (2 8) (3 20) (16 11) (13 7) 9 

2. sort these pairs - make a Pair struct from them and push this struct into a new container called MAIN
(15 18) (4 6) (1 12) (10 21) (17 19) (5 14) (2 8) (3 20) (11 16) (7 13) 9 

3. form main and pend - main has larger elements, pend has smaller elements: - pass the container of Pairs into a recursive function which will only operate on the Large element of the pair 
M1: 18 6 12 21 19 14 8 20 16 13 9
P1: 15 4  1 10 17  5 2  3 11  7

4. recurse on main until it has one element - the recursive function takes a container of Pairs - uses the larger ones in operations, but then when going back, each Large remembers its Small:
4.0 18 6 12 21 19 14 8 20 16 13 9
4.1 (18 6) (12 21) (19 14) (8 20) (16 13) 9
4.2 (6 18) (12 21) (14 19) (8 20) (13 16) 9
4.3 M2: 18 21 19 20 16 9
    P2:  6 12 14  8 13
5. recurse on main until it has one element:
5.0 18 21 19 20 16 9
5.1 (18 21) (19 20) (16 9)
5.2 (18 21) (19 20) (9 16)
5.3 M3: 21 20 16
    P3: 18 19  9
6. recurse on main until it has one element:
6.0 21 20 16
6.1 (21 20) 16
6.2 (20 21) 16
6.3 M4: 21 16
    P4: 20
7. recurse on main until it has one element:
7.0 21 16
7.1 (21 16)
7.2 (16 21)
7.3 M5: 21
    P5: 16
--> BASE condition triggered - main has 1 element - create a <int> container and this is what the recursive function returns
- create MAIN container of ints and push the element there:
    M_int: 21
    --> 21 is a pair , so it knows its Small element, so after recursion, the Small elements is put to MAIN based on Jacobsthal, always before their Large
    M_int: 16 21
- return the int container
9. returning out of recursion - sort the pend elemends back - each el in MAIN is Large in a Pair and has Smaller somewhere
- returned final container M_int: 16 21
- pairs to add: 



Program structure:
1. Class holds a container, which is a template Container
2. Separate high-level separate sort functions for different container types if each should be handled a bit differently
3. But shared logic using templated containers in helper functions like insertionSort, merge, FindJacobsthalNumbers ... 

Tests:
1. duplicates (handling up to student)
2. 1 number, 2 numbers
3. no argument - ./PmergeMe 
4. wrong arguments - a, ., > MAX_INT, ...
5. empty argument - ./PmergeMe  1 2 "" "   " 5
6. negative number cannot wrap - we are casting to unsigned int 