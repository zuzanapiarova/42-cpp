#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP  

#include <cstdlib>   // rand()
#include <ctime> // time()

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;

    public:
        RobotomyRequestForm();
        RobotomyRequestForm(const std::string& target);
        RobotomyRequestForm(const RobotomyRequestForm& origin);
        RobotomyRequestForm& operator =(const RobotomyRequestForm& origin);
        ~RobotomyRequestForm();

        const std::string& getTarget() const;
        bool execute(const Bureaucrat& executor) const;
};

#endif