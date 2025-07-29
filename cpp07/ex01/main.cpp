#include "iter.hpp"

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