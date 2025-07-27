#include "Serializer.hpp"

int main()
{
    // creating pointers
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

    // testing execution - 10 proper, 1 NULL pointer
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
    // testing deserialize getting 0
    try
    {
        Data* c = Serializer::deserialize(0);
        std::cout << "Deserialized: " << c->value << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    // test memory, esp. with exceptions/errors 
    delete a[size];
    return 0;
}