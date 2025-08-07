#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string target;

    public:
        PresidentialPardonForm();
        PresidentialPardonForm(const std::string& target);
        PresidentialPardonForm(const PresidentialPardonForm& origin);
        PresidentialPardonForm& operator =(const PresidentialPardonForm& origin);
        ~PresidentialPardonForm();

        const std::string& getTarget() const;
        bool execute(const Bureaucrat& executor) const;
};

#endif