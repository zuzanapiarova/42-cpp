#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
    Bureaucrat Bureaucrat1("Anna", 6);
    std::cout << Bureaucrat1 << std::endl << std::endl;
    
    // checking ShrubberyCreation Form (S:145, E:137)
    ShrubberyCreationForm s("Garden");
    std::cout << s << std::endl;
    Bureaucrat1.signForm(s); // works - Anna has access to sign
    Bureaucrat1.executeForm(s); // works - Anna has access to execute
    std::cout << s << std::endl << std::endl;
    
    // testing RobotomyReqestForm (S:72, E:45)
    RobotomyRequestForm r("Smart Robot");
    std::cout << r << std::endl;
    Bureaucrat1.executeForm(r); // does not work - Form is not signed yet 
    Bureaucrat1.signForm(r); // sign the form
    Bureaucrat1.executeForm(r); // signed the form, now it works, Anna has execute acess
    std::cout << r << std::endl << std::endl;
    
    // checking PresidentialPardonForm (S:25, E:5)
    PresidentialPardonForm p("Pardoned Person");
    std::cout << p << std::endl;
    Bureaucrat1.signForm(p); // Anna can sign the form, she has access
    Bureaucrat1.executeForm(p); // but she does not have execute access, so it throws an exception
    Bureaucrat1.incrementGrade(); // increment Anna's grade so she has access to execute
    Bureaucrat1.executeForm(p); // now it works, Anna has execute access
    std::cout << p << std::endl << std::endl;

    // testing default constructor - is it handled? 
    ShrubberyCreationForm sDefault;
    RobotomyRequestForm rDefault;
    PresidentialPardonForm pDefault;
    std::cout << sDefault << std::endl; // trying to create empty form - should work(if not, at least do not break)
    std::cout << rDefault << std::endl; // trying to create empty form - should work(if not, at least do not break)
    std::cout << pDefault << std::endl; // trying to create empty form - should work(if not, at least do not break)
    std::cout << std::endl;

    // testing copy constructors
    ShrubberyCreationForm s1(s);
    RobotomyRequestForm r1(r);
    PresidentialPardonForm p1(p);
    // PresidentialPardonForm p1(s); // does not work - cannot create a Form type from a different from type
    std::cout << s1 << std::endl;// should be signed since the origin one was signed
    std::cout << r1 << std::endl;// should be signed since the origin one was signed
    std::cout << p1 << std::endl;// should be signed since the origin one was signed
    std::cout << std::endl;

    // testing copy assignment operators
    ShrubberyCreationForm sCopy;
    RobotomyRequestForm rCopy;
    PresidentialPardonForm pCopy;
    sCopy = s1;
    rCopy = r1;
    pCopy = p1;
    std::cout << sCopy << std::endl;// should be signed since the origin one was signed
    std::cout << rCopy << std::endl;// should be signed since the origin one was signed
    std::cout << pCopy << std::endl;// should be signed since the origin one was signed
    std::cout << std::endl;

    return 0;
}
