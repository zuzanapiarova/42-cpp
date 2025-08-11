#include "Serializer.hpp"

Serializer::Serializer()
{
    std::cout << "Serializer default constructor called." << std::endl;
};

Serializer::Serializer(const Serializer& origin)
{
    std::cout << "Serializer copy constructor called." << std::endl;
    (void)origin;
};

Serializer& Serializer::operator =(const Serializer& origin)
{
    std::cout << "Serializer copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cout << "Copy assignment returns same object." << std::endl;
    return *this;
};

Serializer::~Serializer()
{
    std::cout << "Serializer destructor called." << std::endl;
};

uintptr_t Serializer::serialize(Data* ptr)
{
    // if (!ptr) throw std::invalid_argument("Cannot serialize null pointer");
    return reinterpret_cast<uintptr_t>(ptr);
};

Data* Serializer::deserialize(uintptr_t raw)
{
    Data* ptr = reinterpret_cast<Data*>(raw);
    if (!ptr) throw std::runtime_error("Deserialized pointer is null");
    return ptr;
};