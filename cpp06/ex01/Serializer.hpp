#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <iostream>
#include <string>
#include <stdint.h> // uintptr_
#include "data.h" 

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer& origin);
        Serializer& operator =(const Serializer& origin);
        ~Serializer();

    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);

};

#endif