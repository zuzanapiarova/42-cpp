#include "Serializer.hpp"

Serializer::Serializer()
{
    std::cout << "Serializer default constructor called." << std::endl;
};

uintptr_t Serializer::serialize(Data* ptr)
{
    if (!ptr) throw std::invalid_argument("Cannot serialize null pointer");
    return reinterpret_cast<uintptr_t>(ptr);
};

Data* Serializer::deserialize(uintptr_t raw)
{
    Data* ptr = reinterpret_cast<Data*>(raw);
    if (!ptr) throw std::runtime_error("Deserialized pointer is null");
    return ptr;
};