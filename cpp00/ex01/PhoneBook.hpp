#ifndef PHONE_BOOK_H
# define PHONE_BOOK_H

# include <iostream>
# include <string>
# include <iomanip> // formatting

# include "Contact.hpp"

class PhoneBook
{
    private:
        Contact contacts[8];
        int count;

    public:
        PhoneBook();
        ~PhoneBook();

        bool addContact();
        bool getContact(int index) const;
        void displayContacts() const;
};

#endif