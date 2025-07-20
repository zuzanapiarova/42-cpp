#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    try
    {
        Bureaucrat a("Anna", 120);
        Bureaucrat b("Bob", 20);
        Form c("Contract", 20, 10);
        Form d("Contract", 20, 10);

        b.signForm(c); // works - Bob has access
        std::cout << c.getIsSigned() << std::endl;

        b.decrementGrade();
        
        b.signForm(d); // does not work - Bob has not access anymore
        std::cout << d.getIsSigned() << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << "Found exception " << e.what() << std::endl;
    }
        

    return 0;
}