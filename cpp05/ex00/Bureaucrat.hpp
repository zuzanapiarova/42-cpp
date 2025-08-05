#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <string>
#include <iostream>

#include "GradeExceptions.hpp"

class Bureaucrat
{
    private:
        const std::string   name;
        int                 grade;
    
    public:
        Bureaucrat(const std::string& new_name, const int new_grade);
        Bureaucrat(const Bureaucrat& origin);
        Bureaucrat& operator =(const Bureaucrat& origin);
        ~Bureaucrat();

        std::string getName() const;
        int         getGrade() const;
        void        incrementGrade();
        void        decrementGrade();

};

std::ostream& operator << (std::ostream& os, const Bureaucrat& bureaucrat);

#endif