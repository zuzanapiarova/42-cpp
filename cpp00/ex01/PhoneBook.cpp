#include "PhoneBook.hpp"
#include <limits>

//------------------------------------------------------------ Helper Functions -------------------------------------------------------------------------

bool isOnlyDigits(const std::string &input)
{
    int i  = 0;
    while (input[i])
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

// -------------------------------------------------------- Orthodox Cannical Form -----------------------------------------------------------------------

// Default constructor
PhoneBook::PhoneBook() : count(0) {}

// Destructor
PhoneBook::~PhoneBook() {}

// ---------------------------------------------------------- Member Functions -----------------------------------------------------------------------

void PhoneBook::menu( void )
{
    while (std::cin)
    {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::string command;
        if (!std::getline(std::cin, command))
            break ;
        else if (std::string(command) == "ADD")
            addContact();
        else if (std::string(command) == "SEARCH")
        {
            displayContacts();
            std::cout << "Enter index of contact you wish to see: ";
            int index;
            if (!(std::cin >> index))
            {
                std::cin.clear(); // clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid leftover input form previous cin calls
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue ;
            }
            printContact(index);
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
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear leftover input form previous cin calls (cin, shen called without readline, can leave characters after the first whitespace in the buffer)
    if (!std::getline(std::cin, input)) 
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

    // check if any is empty
    // change to always overwrite the oldest contact, not the last one 
    if (count == 8)
    {
        contacts[0] = contact;
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