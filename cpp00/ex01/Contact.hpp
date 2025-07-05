#ifndef CONTACT_H
# define CONTACT_H

#include <iostream>
#include <string>

class Contact
{
    private:
        std::string firstName;
        std::string lastName;
        std::string nickname;
        std::string phoneNumber;
        std::string darkSecret;

    public:
        Contact();
        ~Contact();

        void setName(const std::string &name);
        std::string getName() const;

        void setSurname(const std::string &surname);
        std::string getSurname() const;

        void setNickname(const std::string &nickname);
        std::string getNickname() const;

        void setPhone(const std::string &phone);
        std::string getPhone() const;

        void setSecret(const std::string &secret);
        std::string getSecret() const;

};

#endif