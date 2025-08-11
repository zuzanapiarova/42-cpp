#include "Serializer.hpp"

// questions:
// 1. do the classes in all excercises need cannonical form? 
// 2. can i have a c data struct for data ?  

int main()
{
    // creating pointers
    int size = 5;
    Data* a[size];
    
    int i = 0;
    while (i < size)
    {
        a[i] = new Data();
        a[i]->value = i;
        i++;
    }
    a[size] = NULL;

    // testing execution - all besides last proper, 1 last is NULL pointer to test deserialize getting 0
    i = 0;
    while (i <= size)
    {
        try
        {
            uintptr_t b = Serializer::serialize(a[i]);
            std::cout << "Serialized: " << b << std::endl;
    
            Data* c = Serializer::deserialize(b);
            std::cout << "Deserialized: " << c << " with value " << c->value << std::endl;
    
            // the deserialized pointer must equal the pointer from which it was serialized
            std::cout << c << " ?= " << a[i] << std::endl;
            if (c == a[i])
                std::cout << "The pointer is the same after serialization and deserialization." << std::endl;
            else
                std::cout << "The pointer is differenet after serialization and deserialization." << std::endl;
            std::cout << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
        i++;
    }
    // test memory, esp. with exceptions/errors 
    i = 0;
    while (i < size)
    {
        delete a[i];
        i++;
    }
    return 0;
};