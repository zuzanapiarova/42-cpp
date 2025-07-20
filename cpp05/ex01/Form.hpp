#ifndef FORM_H
# define FORM_H

#include <string>
#include <iostream>

#include "Bureaucrat.hpp"

class Form
{
    private:
        const std::string&  name;
        bool                isSigned;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
        Form(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade);
        Form(const Form& origin);
        Form& operator =(const Form& origin);
        ~Form();

        std::string getName() const;
        bool        getIsSigned() const;
        int         getMinimumSignGrade() const;
        int         getMinimumExecutionGrade() const;
        void        beSigned(const Bureaucrat& bureaucrat);

        class       GradeTooHighException;
        class       GradeTooLowException;   

};

std::ostream& operator << (std::ostream& os, const Form& form);

class Form::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw()
        {   
            return "Grade too high for Form!";
        }
};

class Form::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Grade too low for Form!";
        }
};

#endif