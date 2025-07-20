#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(const std::string& new_name, const int new_grade) : name(new_name)
{
    std::cout << "Bureaucrat default constructor called." << std::endl;
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