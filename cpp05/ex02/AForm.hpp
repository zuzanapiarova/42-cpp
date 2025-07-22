#ifndef AFORM_H
# define AFORM_H

#include <string>
#include <iostream>

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented
class Bureaucrat;

class AForm
{
    private:
        const std::string&  name;
        bool                isSigned;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
        AForm(const std::string& newName, const int newMinimumSignGrade, const int newMinimumExecutionGrade);
        AForm(const AForm& origin);
        AForm& operator =(const AForm& origin);
        ~AForm();

        const std::string getName() const;
        const bool        getIsSigned() const;
        const int         getMinimumSignGrade() const;
        const int         getMinimumExecutionGrade() const;
        void        beSigned(const Bureaucrat& bureaucrat);
        void execute(const Bureaucrat& executor) const ; // !!!!!!!!!!


        class       GradeTooHighException;
        class       GradeTooLowException;   

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

#endif