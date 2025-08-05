#ifndef AFORM_H
# define AFORM_H

#include <string>
#include <iostream>

#include "GradeExceptions.hpp"

// preventing circular dependencies - forweard declaration of just the class here, the header is included where it is implemented
class Bureaucrat;

class AForm
{
    private:
        const std::string   name;
        const int           minimumSignGrade;
        const int           minimumExecutionGrade;
        bool                isSigned;
        int                 checkGrade(int grade, int minGrade, int maxGrade);
    
    public:
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

};

#endif