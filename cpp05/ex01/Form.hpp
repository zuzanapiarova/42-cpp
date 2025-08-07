#ifndef FORM_H
# define FORM_H

#include <string>
#include <iostream>
#include <exception>

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented - do not include the Bureaucrat header hpp file
class Bureaucrat;

class Form
{
    private:
        const std::string   name;
        bool                isSigned;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
        Form();
        Form(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade);
        Form(const Form& origin);
        Form& operator =(const Form& origin);
        ~Form();

        std::string getName() const;
        bool        getIsSigned() const;
        int         getMinimumSignGrade() const;
        int         getMinimumExecutionGrade() const;
        void        beSigned(const Bureaucrat& bureaucrat); 

        class GradeTooHighException;
        class GradeTooLowException;

};

std::ostream& operator << (std::ostream& os, const Form& form);

class Form::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw();
};

class Form::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw();
};

#endif