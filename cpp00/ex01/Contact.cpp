#include "Contact.hpp"

// Default constructor
Contact::Contact() : firstName(""), lastName(""), nickname(""), phoneNumber(""), darkSecret("") {}

// Destructor
Contact::~Contact() {}

// Setters
void Contact::setName(const std::string &name)
{
    firstName = name;
}

void Contact::setSurname(const std::string &surname)
{
    lastName = surname;
}

void Contact::setNickname(const std::string &nick)
{
    nickname = nick;
}

void Contact::setPhone(const std::string &phone)
{
    phoneNumber = phone;
}

void Contact::setSecret(const std::string &secret)
{
    darkSecret = secret;
}

// Getters
std::string Contact::getName() const
{
    return firstName;
}

std::string Contact::getSurname() const
{
    return lastName;
}

std::string Contact::getNickname() const
{
    return nickname;
}

std::string Contact::getPhone() const
{
    return phoneNumber;
}

std::string Contact::getSecret() const
{
    return darkSecret;
}
