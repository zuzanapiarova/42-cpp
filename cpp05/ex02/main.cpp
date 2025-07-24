#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// !!!! protect agains empty target in the 3 forms and other empty fields in the AForm and Bureaucrat classes

int main(void)
{
    Bureaucrat a("Anna", 6);
    ShrubberyCreationForm s("Garden");
    std::cout << a << std::endl;

    std::cout << "Name before signing: " << s.getName() << std::endl;

    a.signForm(s); // works - Anna has access to sign

    std::cout << "Name after signing: " << s.getName() << std::endl;
    std::cout << "Is signed: " << s.getIsSigned() << std::endl;
    std::cout << "Sign grade: " << s.getMinimumSignGrade() << std::endl;

    a.executeForm(s); // works - Anna has access to execute
    std::cout << s << std::endl << std::endl;
    
    // RobotomyRequestForm r("Smart Robot");
    // PresidentialPardonForm p("Pardoned Person");
    
    std::cout << std::endl;
    
    // a.executeForm(r); // does not work - Form is not signed yet 
    // a.signForm(r); // sign the form
    // a.executeForm(r); // signed the form, now it works, Anna has execute acess
    // std::cout << r << std::endl << std::endl;

    // a.signForm(p); // Anna can sign teh form, she has access
    // a.executeForm(p); // but she does not have execute access, so it throws an exception
    // a.incrementGrade(); // increment Anna's grade so she has access to execute
    // a.executeForm(p); // now it works, Anna has execute access
    // std::cout << p << std::endl << std::endl;

    return 0;
}
