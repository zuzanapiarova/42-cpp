#include "PhoneBook.hpp"

// Default constructor
PhoneBook::PhoneBook() : count(0) {}

// Destructor
PhoneBook::~PhoneBook() {}

bool PhoneBook::addContact()
{
    Contact contact;
    std::string input;

    std::cout << "Enter first name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear leftover input form previous cin calls
    std::getline(std::cin, input);
    contact.setName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    contact.setSurname(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    contact.setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    contact.setPhone(input);

    std::cout << "Enter a dark secret for this contact: ";
    std::getline(std::cin, input);
    contact.setSecret(input);
    // check if any is empty
    if (count == 8)
    {
        contacts[7] = contact; 
        std::cout << "Phone book full. Overwriting the last contact." << std::endl;
    }
    else
    {
        contacts[count] = contact;
        ++count;
        std::cout << "Contact added successfully!" << std::endl;
    }
    return true;
}

std::string formatField(const std::string& str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    else
        return std::string(10 - str.length(), ' ') + str;
}

void PhoneBook::displayContacts() const
{
    std::cout << std::setw(10) << "Index"      << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name"  << "|"
              << std::setw(10) << "Nickname"   << std::endl;
    
    if (count == 0)
    {
        std::cout << "PhoneBook is empty." << std::endl;
        return ;
    }

    for (int i = 0; i < count; ++i)
    {
        std::cout << std::setw(10) << i + 1 << "|"
                  << formatField(contacts[i].getName())     << "|"
                  << formatField(contacts[i].getSurname())  << "|"
                  << formatField(contacts[i].getNickname()) << std::endl;
    }
}

bool PhoneBook::getContact(int index) const
{
    if (index <= 0 || index > count)
    {
        std::cout << "Invalid contact index." << std::endl;
        return false;
    }

    const Contact &c = contacts[index - 1];

    std::cout << "First name: "     << c.getName()     << std::endl;
    std::cout << "Last name: "      << c.getSurname()  << std::endl;
    std::cout << "Nickname: "       << c.getNickname() << std::endl;
    std::cout << "Phone number: "   << c.getPhone()    << std::endl;
    std::cout << "Darkest secret: " << c.getSecret()   << std::endl;
    return true;
}