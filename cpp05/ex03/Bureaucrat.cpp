#include "Bureaucrat.hpp"

// ---------------------------------------------- Orthodox Canonical Form -------------------------------------------------

Bureaucrat::Bureaucrat(const std::string& new_name, const int new_grade) : name(new_name)
{
    std::cout << "Bureaucrat overload constructor called." << std::endl;
    if (new_grade < 1)
        throw GradeTooHighException();
    else if (new_grade > 150)
        throw GradeTooLowException();
    grade = new_grade;
};

Bureaucrat::Bureaucrat(const Bureaucrat& origin) : name(origin.name)
{
    std::cout << "Bureaucrat copy constructor called." << std::endl;
    if (origin.grade < 1)
        throw GradeTooHighException();
    else if (origin.grade > 150)
        throw GradeTooLowException();
    this->grade = origin.grade;
};

Bureaucrat& Bureaucrat::operator = (const Bureaucrat& origin)
{
    std::cout << "Bureaucrat copy assignment operator called." << std::endl;
    if (this != &origin)
    {
        if (origin.grade < 1)
            throw GradeTooHighException();
        else if (origin.grade > 150)
            throw GradeTooLowException();
        this->grade = origin.grade;
    }
    return *this;
};

std::ostream& operator <<(std::ostream& os, const Bureaucrat& bureaucrat)
{
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return os;
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat destructor called." << std::endl;
};

// ---------------------------------------------- Member Functions -------------------------------------------------

std::string Bureaucrat::getName() const
{
    return name;
};

int         Bureaucrat::getGrade() const
{
    return grade;
};

void        Bureaucrat::incrementGrade()
{
    if (grade <= 1)
        throw GradeTooHighException();
    else if (grade > 150)
        throw GradeTooLowException();
    else
        grade--;
};

void        Bureaucrat::decrementGrade()
{
    if (grade < 1)
        throw GradeTooHighException();
    else if (grade >= 150)
        throw GradeTooLowException();
    else
        grade++;
};   

void    Bureaucrat::signForm(AForm& form) const
{
    try
    {
        form.beSigned(*this);
        std::cout << "Bureaucrat " << name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Bureaucrat " << name << " couldn’t sign " << form.getName() << " because " << e.what() << std::endl;
    }
}

void   Bureaucrat::executeForm(const AForm& form) const
{
    try
    {
        form.execute(*this);
        std::cout << "Bureaucrat " << name << " executed " << form.getName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Bureaucrat " << name << " couldn’t execute " << form.getName() << " because " << e.what() << std::endl;
    }
}
