#include "Contact.hpp"
#include "PhoneBook.hpp"

int main()
{
    PhoneBook pb;

    while (1)
    {
        std::string command;
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::cin >> command;
        if (std::string(command) == "ADD")
            pb.addContact();
        else if (std::string(command) == "SEARCH")
        {
            pb.displayContacts();
            std::cout << "Enter index of contact you wish to see: ";
            int index;
            std::cin >> index;
            pb.getContact(index);
        }
        else if (std::string(command) == "EXIT")
        {
            // cleanup?
            return 0;
        }
    }
    return 0;
}