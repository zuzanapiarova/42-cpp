#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery Creation Form", 145, 137), target("Unassigned")
{
    std::cout << "ShrubberyCreationForm default constructor called for target " << target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation Form", 145, 137), target(target)
{
    std::cout << "ShrubberyCreationForm constructor called for target " << target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& origin)
    : AForm(origin), target(origin.target)
{
    std::cout << "ShrubberyCreationForm copy constructor called." << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator =(const ShrubberyCreationForm& origin)
{
    std::cout << "ShrubberyCreationForm copy assignment operator called." << std::endl;
    if (this != &origin)
        std::cerr << "Cannot use copy assignment on object with const members. Aborting without change." << std::endl;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "ShrubberyCreationForm destructor called for target " << target << std::endl;
}

// -------------------------------------------- Member Functions -----------------------------------------

const std::string& ShrubberyCreationForm::getTarget() const
{
    return target;
};

bool    ShrubberyCreationForm::execute(const Bureaucrat& executor ) const 
{
    if (!getIsSigned())
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > getMinimumExecutionGrade())
        throw AForm::GradeTooLowException();
    std::ofstream outputFile(target.c_str());
    if (!outputFile)
    {
        std::cerr << target << ": file cannot be opened or created or other error." << std::endl;
        return false;
    }
    outputFile << "        *                ********" << std::endl;
    outputFile << "       ***            **************" << std::endl;
    outputFile << "      *****        ********************" << std::endl;
    outputFile << "     *******      **********************" << std::endl;
    outputFile << "    *********      ********************" << std::endl;
    outputFile << "   ***********        **************" << std::endl;
    outputFile << "  *************             |||" << std::endl;
    outputFile << " ***************            |||" << std::endl;
    outputFile << "        |||                 |||" << std::endl;
    outputFile << "        |||                 |||" << std::endl;
    outputFile.close();
    std::cout << "Shrubbery Execution Form executed - check " << target << " file !" << std::endl;

    return 0;
}
