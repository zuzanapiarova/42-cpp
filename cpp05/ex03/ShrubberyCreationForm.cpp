#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation Form", 145, 137), targetFileName(target)
{
    std::cout << "ShrubberyCreationForm constructor called for target " << targetFileName << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& origin)
    : AForm("Shrubbery Creation Form", 145, 137), targetFileName(origin.targetFileName)
{
    std::cout << "ShrubberyCreationForm copy constructor called." << std::endl;
    *this = origin;
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
    std::cout << "ShrubberyCreationForm destructor called for target " << targetFileName << std::endl;
}

// -------------------------------------------- Member Functions -----------------------------------------

const std::string& ShrubberyCreationForm::getTargetFileName() const
{
    return targetFileName;
};

bool    ShrubberyCreationForm::execute(const Bureaucrat& executor ) const 
{
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getMinimumExecutionGrade())
        throw GradeTooLowException();
    std::ofstream outputFile(targetFileName.c_str());
    if (!outputFile)
    {
        std::cerr << targetFileName << ": file cannot be opened or created or other error." << std::endl;
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

    return 0;
}
