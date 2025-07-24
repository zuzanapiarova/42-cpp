#ifndef AFORM_H
# define AFORM_H

#include <string>
#include <iostream>

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented
class Bureaucrat;

class AForm
{
    protected:
        const std::string&  name;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        bool                isSigned;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
        AForm(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade);
        AForm(const AForm& origin);
        AForm& operator =(const AForm& origin);
        virtual ~AForm();

        virtual std::string   getName() const;
        virtual bool          getIsSigned() const;
        virtual int           getMinimumSignGrade() const;
        virtual int           getMinimumExecutionGrade() const;
        virtual void          beSigned(const Bureaucrat& bureaucrat);
        virtual bool          execute(const Bureaucrat& executor) const = 0;

        class       GradeTooHighException;
        class       GradeTooLowException;   
        class       FormNotSignedException;

};

std::ostream& operator << (std::ostream& os, const AForm& form);

class AForm::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw()
        {   
            return "Grade too high for Form!";
        }
};

class AForm::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Grade too low for Form!";
        }
};
class AForm::FormNotSignedException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Form is not signed!";
        }
};

#endif