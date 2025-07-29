#include "Array.hpp"

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
