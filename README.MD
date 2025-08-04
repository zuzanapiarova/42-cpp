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

## CPP06 - Casting

#### Excercise 0 - Function pointers again

This excercise taught us to safely cast among the primitive data types and between string and primitive data types. We had to think of many possible error situations.

Tests:

A. wrong input - does not match any types string literal
1. af
2. 0.4ff
3. --0.222
4. 1.f - float ending with .
5. 1. - double ending with .
6. '' - empty string
7. .f 
8. 1f - not valid string literal in cpp but can possibly handle it

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
19. 298 - checks if wrapping is handled - if not, prints *

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
35. '\j' - invalid escape sequence
36. 2147483649 - < max int
37. 100000000000000000000000000000000000000000000000.0f - < max float
38. max double can hardly be tested since it is ~1.8 × 10^308

#### Excercise 1 - casting pointers - reinterpret cast

This excercise taught us how to work with reinterpret casting. 
- reinterpret_cast = used for low-level casting between unrelated types like pointers and integers
- uintptr_t = unsigned integer type that can safely hold a pointer

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

#### Excercise 02 - dynamic casts

Dynamic cast only works with polymorphic types (that at least one virtual function) and only on pointers/references. 

This excercise shows us difference between dynamic casts to pointers and to references. 

- dynamic cast to pointer = it’s non-throwing, so no try-catch is needed, if fails, returns nullptr - you can check each cast afterwards with if (ptr) safely, works even if the pointer is nullptr
- dynamic cast to reference = if cast fails, throws std::bad_cast exception, so must wrap it in a try-catch block and if checking for multiple types, check the rest in this block, reference must be non-null, so we do not have to check for nullptr because it will never happed

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

## CPP07 - Casting

#### Excercise 0 - Function templates

This excercise introduces function templates. What is important to know is to always define (declare+implement) it in header file, because compiler must see the definition then it instantiates the funciton with the type it received. 

Pass in references or pointers where possible to avoid copying large objects. 

```
template <typename T, U>
T functionName(T& x, U& y) {}
```

Test (from subject):
```
int
main( void )
{
    int a = 2;
    int b = 3;
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
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
    int size = 5;

    // some arrays of different types 
    char char_arr[] = { '!', '"', '#', '$', '%' };
    const char c_char_arr[] = { '^', '&', '*', '(', ')' };
    int int_arr[] = { 1, 2, 3, 4, 5 };
    const int c_int_arr[] = { 100, 200, 300, 400, 500 };
    std::string str_arr[] = { "Dog", "Cat", "Cow", "Mouse", "Tiger" };
    const std::string c_str_arr[] = { "Giraffe", "Monkey", "Bug", "Elephant", "Wolf" };

    // passing in functions
    ::iter(int_arr, size, add_one); // --> works - int arr, int function
    ::iter(int_arr, size, print_int_arr); // --> works - int arr, int template function
    //::iter(char_arr, size, add_one); // --> does not work - char arr, int function
    std::cout << std::endl << std::endl;
    
    // passing in template functions:
    ::iter(char_arr, size, add); // --> works - char arr, template function
    ::iter(char_arr, size, print_arr_el); // --> works - char arr, const template function
    std::cout << std::endl;
    //::iter(c_char_arr, size, add); // --> does not work -  const char arr, non-const template function that tries to modify the array
    ::iter(c_char_arr, size, print_arr_el); // --> works - const char arr, const template function
    std::cout << std::endl << std::endl;

    ::iter(int_arr, size, add); // --> works - int arr, non-const template function
    ::iter(int_arr, size, print_arr_el); // --> works - int arr, const template function
    std::cout << std::endl;
    //::iter(c_int_arr, size, add); // --> does not work - const array, non-const template function add tries to modify the array
    ::iter(c_int_arr, size, print_arr_el); // --> works - const array, const template function
    std::cout << std::endl << std::endl;

    ::iter(str_arr, size, add); // --> works - int arr, template function
    ::iter(str_arr, size, print_arr_el); // --> works  - string arr, template function
    std::cout << std::endl;
    //::iter(c_str_arr, size, add); // --> does not work - const array, non-const template function add tries to modify the array
    ::iter(c_str_arr, size, print_arr_el); // --> works - const string array, const template function
    std::cout << std::endl <<std::endl;

    // edge cases tests
    ::iter<int>(NULL, size, print_int_arr); // should safely do nothing
    ::iter(int_arr, 0, print_int_arr); // empty array, prints nothing
    ::iter(int_arr, 1, print_int_arr); // small array, runs once

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
2. check that the array cretaed with default constructor exists but its empty and that the size is initialized
3. check that the array created with overload constructor is value-initialized with default values for their data type - there is () after new T[n]() in overload constructor!
4. do assignment from array that has size 0, check valgrind and print the [0] value
5. copy the same element with copy assignment operator - should not do anything - check the values 
6. test the size() function on empty and non-empty array
7. test out of bounds access - should throw exception
```
int main( void )
{
    int size = 5;

    try
    {
        // empty array with default constructor - should have size 0 and _array initialized to NULL
        Array<int> emptyArr;
        std::cout << "Empty array size: " << emptyArr.size() << std::endl << std::endl;
        //std::cout << "Empty array[0]: " << emptyArr[0]; // throws out of bounds exception

        // int array created with overload constructor - should have size n and values are initialized to default value of provided data type
        Array<int>intArr(size);
        std::cout << "Int array size: " << intArr.size() << std::endl;
        for (unsigned int i = 0; i < intArr.size(); ++i)
            std::cout << intArr[i] << ", ";
        std::cout << std::endl << std::endl;

        // string array created with overload constructor - must be value-initialized
        Array<std::string>strArr(size);
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

        // test copy constructor
        //Array<char> charArr(strArr); // does not work - not allowed - trying to construct from different type
        const Array<std::string> otherStrArr(strArr);
        std::cout << "Other string array size: " << otherStrArr.size() << std::endl;
        for (unsigned int i = 0; i < otherStrArr.size(); ++i)
            std::cout << otherStrArr[i] << ", ";
        std::cout << std::endl << std::endl;

        // const string array - works as others, but does not allow a[10] = ...
        const Array<std::string>constStrArr(size);
        //constStrArr[0] = "Cow"; // does not work - not allowed - trying to reassign const element

        // testing copy assignment operator for size 0 - Empty Array
        Array<int> newIntArr(5);
        newIntArr = emptyArr;
        std::cout << "New Int array size: " << newIntArr.size() << std::endl << std::endl;

        // testing copy assignment operator for size 
        intArr[0] = 42;
        newIntArr = intArr;
        std::cout << "New Int array size: " << newIntArr.size() << std::endl << std::endl;
        for (unsigned int i = 0; i < newIntArr.size(); ++i)
            std::cout << newIntArr[i] << ", ";
        std::cout << std::endl << std::endl;

        // testint copying the same element with copy assignment operator --> should do nothing
        // intArr = intArr;
        // std::cout << "Int array size: " << intArr.size() << std::endl << std::endl;
        // for (unsigned int i = 0; i < intArr.size(); ++i)
        //     std::cout << intArr[i] << ", ";
        // std::cout << std::endl << std::endl;

        // accessing invalid element - should raise exception
        std::cout << "Trying to access invalid element of Int array: " << intArr[6] << "." << std::endl << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

## CPP08

#### Excercise 00 - Containers and iterators

This excercise teached usabout basic containers and iterators. 

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

    try {

        std::vector<int>::iterator it1 = easyfind(vec, 1); // element exists
        std::cout << "Found in vector: " << *it1 << std::endl;

        std::list<int>::const_iterator it2 = easyfind(lst, 300);  // element exists - const container
        std::cout << "Found in list: " << *it2 << std::endl;

        std::vector<int>::const_iterator it3 = easyfind(duplicates, 2);  // duplicate elements - gets the first occurence
        std::cout << "Found in list: " << *it3 << " on index: " << it3 - duplicates.begin() << std::endl;

        std::deque<int>::const_iterator it4 = easyfind(empty, 1);  // empty container - element is not found
        std::cout << "Found in list: " << *it4 << std::endl;

        std::deque<int>::iterator it5 = easyfind(deque, 0); // outside of container
        std::cout << "Found in deque: " << *it5 << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```

#### Excercise 01 - Iterators 

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
