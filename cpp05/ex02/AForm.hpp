#ifndef AFORM_H
# define AFORM_H

#include <string>
#include <iostream>
#include <exception>

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented
class Bureaucrat;

class AForm
{
    private:
        const std::string   name;
        bool                isSigned;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
        AForm();
        AForm(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade);
        AForm(const AForm& origin);
        AForm& operator =(const AForm& origin);
        virtual ~AForm();

        virtual const std::string&  getName() const;
        virtual bool          getIsSigned() const;
        virtual int           getMinimumSignGrade() const;
        virtual int           getMinimumExecutionGrade() const;
        virtual void          beSigned(const Bureaucrat& bureaucrat);
        virtual bool          execute(const Bureaucrat& executor) const = 0;

        class GradeTooHighException;
        class GradeTooLowException;
        class FormNotSignedException;

};

std::ostream& operator << (std::ostream& os, const AForm& form);

class AForm::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw();
};

class AForm::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw();
};

class AForm::FormNotSignedException : public std::exception
{
    public:
        const char* what() const throw();
};

#endif