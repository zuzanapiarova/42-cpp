#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation Form", 145, 137), targetFileName(target)
{
    std::cout << "ShrubberyCreationForm constructor called for target: " << targetFileName << std::endl;
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
    {
        AForm::operator=(origin);
        targetFileName = origin.targetFileName;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "ShrubberyCreationForm destructor called for target: " << targetFileName << std::endl;
}

// -------------------------------------------- Member Functions -----------------------------------------

const std::string& ShrubberyCreationForm::getTargetFileName() const
{
    return targetFileName;
};

bool    ShrubberyCreationForm::execute(const Bureaucrat& executor ) const 
{
    if (!getIsSigned())
    {
        throw AForm::FormNotSignedException();
    }
    if (executor.getGrade() > getMinimumExecutionGrade())
    {
        throw AForm::GradeTooLowException();
    }
    std::ofstream outputFile(targetFileName);
    if (!outputFile)
    {
        std::cerr << targetFileName << ": file cannot be opened or created or other error." << std::endl;
        return false;
    }
    outputFile << "ASCII Art Tree" << std::endl;
    outputFile << "        *" << std::endl;
    outputFile << "       ***" << std::endl;
    outputFile << "      *****" << std::endl;
    outputFile << "     *******" << std::endl;
    outputFile << "    *********" << std::endl;
    outputFile << "   ***********" << std::endl;
    outputFile << "  *************" << std::endl;
    outputFile << " ***************" << std::endl;
    outputFile << "        |||" << std::endl;
    outputFile << "        |||" << std::endl;
    outputFile << "        |||" << std::endl;
    outputFile.close();

    return true;
};