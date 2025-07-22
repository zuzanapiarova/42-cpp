#ifndef SHRUBBERY_CREATION_FORM_HPP
#define SHRUBBERY_CREATION_FORM_HPP   

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
    private:
        std::string targetFileName;

    public:
        ShrubberyCreationForm(const std::string& target);
        ShrubberyCreationForm(const ShrubberyCreationForm& origin);
        ShrubberyCreationForm& operator =(const ShrubberyCreationForm& origin);
        ~ShrubberyCreationForm();

        const std::string& getTarget() const ;

};

#endif