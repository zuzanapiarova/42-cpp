#ifndef FORM_H
# define FORM_H

#include <string>
#include <iostream>

#include "GradeExceptions.hpp"

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented
class Bureaucrat;

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

};

std::ostream& operator << (std::ostream& os, const Form& form);

#endif