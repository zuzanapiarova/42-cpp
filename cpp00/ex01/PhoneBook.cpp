#include "PhoneBook.hpp"

//------------------------------------------------------------ Helper Functions -------------------------------------------------------------------------

bool isOnlyDigits(const std::string &input)
{
    int i  = 0;
    while (input[i])
    {
        if (!isdigit(input[i]))
            return false;
        i++;
    }
    return true;
}

// -------------------------------------------------------- Orthodox Cannical Form -----------------------------------------------------------------------

// Default constructor
PhoneBook::PhoneBook() : count(0), oldestIndex(0)
{
    std::cout << "PhoneBook default constructor called." << std::endl;
};

// Destructor
PhoneBook::~PhoneBook()
{
    std::cout << "PhoneBook destructor called." << std::endl;
};

// ---------------------------------------------------------- Member Functions -----------------------------------------------------------------------

void PhoneBook::menu( void )
{
    std::string command;

    while (std::cout << "Enter a command (ADD, SEARCH, EXIT): " && std::getline(std::cin, command))
    {
        if (std::string(command) == "ADD")
        {
            if  (addContact() == false)
                break ;
        }
        else if (std::string(command) == "SEARCH")
        {
            displayContacts();
            std::cout << "Enter index of contact you wish to see: ";
            std::string indexStr;
            if  (!std::getline(std::cin, indexStr) || indexStr.empty() || !isOnlyDigits(indexStr))
            {
                std::cout << "Invalid input. Please enter a valid number." << std::endl;
                break ;
            }
            printContact(std::atoi(indexStr.c_str()));
        }
        else if (std::string(command) == "EXIT")
            break ;
    }
}

bool PhoneBook::addContact()
{
    Contact contact;
    std::string input;

    std::cout << "Enter first name: ";
    if (!std::getline(std::cin, input) || input.empty()) 
    {
        std::cout << "First name cannot be empty. Aborting." << std::endl;
        return false;
    }
    contact.setName(input);

    std::cout << "Enter last name: ";
    if (!std::getline(std::cin, input) || input.empty()) 
    {
        std::cout << "Last name cannot be empty. Aborting." << std::endl;
        return false;
    }
    contact.setSurname(input);

    std::cout << "Enter nickname: ";
    if (!std::getline(std::cin, input) || input.empty()) 
    {
        std::cout << "Nickname cannot be empty. Aborting." << std::endl;
        return false;
    }
    contact.setNickname(input);

    std::cout << "Enter phone number: ";
    if (!std::getline(std::cin, input) || input.empty()) 
    {
        std::cout << "Phone number cannot be empty. Aborting." << std::endl;
        return false;
    }
    if (!isOnlyDigits(input)) 
    {
        std::cout << "Phone number can contain only digits. Aborting." << std::endl;
        return false;
    }
    contact.setPhone(input);

    std::cout << "Enter a dark secret for this contact: ";
    if (!std::getline(std::cin, input) || input.empty()) 
    {
        std::cout << "Dark secret cannot be empty. Aborting." << std::endl;
        return false;
    }
    contact.setSecret(input);

    // always overwrite the oldest contact in a circular manner
    if (count < 8)
    {
        contacts[count] = contact;
        ++count;
        std::cout << "Contact added successfully!" << std::endl;
    }
    else
    {
        contacts[oldestIndex] = contact;
        std::cout << "Phone book full. Overwriting the oldest contact." << std::endl;
        oldestIndex = (oldestIndex + 1) % 8;
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
        std::cout << std::setw(10) << i + 1                 << "|"
                  << formatField(contacts[i].getName())     << "|"
                  << formatField(contacts[i].getSurname())  << "|"
                  << formatField(contacts[i].getNickname()) << std::endl;
    }
}

void PhoneBook::printContact(int index) const
{
    if (index <= 0 || index > count)
    {
        std::cout << "Invalid contact index." << std::endl;
        return ;
    }

    const Contact &c = contacts[index - 1];

    std::cout << "First name: "     << c.getName()     << std::endl;
    std::cout << "Last name: "      << c.getSurname()  << std::endl;
    std::cout << "Nickname: "       << c.getNickname() << std::endl;
    std::cout << "Phone number: "   << c.getPhone()    << std::endl;
    std::cout << "Darkest secret: " << c.getSecret()   << std::endl;
    return ;
}