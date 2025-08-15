#include "Array.hpp"

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
