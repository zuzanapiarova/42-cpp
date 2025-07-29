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