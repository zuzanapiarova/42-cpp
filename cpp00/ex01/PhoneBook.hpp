#ifndef PHONE_BOOK_H
# define PHONE_BOOK_H

# include <iostream>
# include <string>
# include <iomanip> // formatting
# include <cstdlib> // atoi
# include <limits> // intmax

# include "Contact.hpp"

class PhoneBook
{
    private:
        Contact contacts[8];
        int count;
        int oldestIndex;

    public:
        PhoneBook();
        ~PhoneBook();

        bool addContact();
        void printContact( int index ) const;
        void displayContacts() const;
        void menu();
};

#endif