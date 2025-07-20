#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <string>
#include <iostream>

class Bureaucrat
{
    private:
        const std::string   name;
        int                 grade;
    
    public:
        class GradeTooLowException;
        class GradeTooHighException;

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


class Bureaucrat::GradeTooHighException : public std::exception
{
    public:
        const char* what() const throw()
        {   
            return "Grade too high!";
        }
};

class Bureaucrat::GradeTooLowException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Grade too low!";
        }
};

#endif