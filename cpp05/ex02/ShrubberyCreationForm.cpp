#include "ShrubberyCreationForm.hpp"

// ----------------------------------------- Orthodox Canonical Form ------------------------------------

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation Form", 145, 137), targetFileName(target)
{
    std::cout << "ShrubberyCreationForm constructor called for target: " << targetFileName << std::endl;
    if (targetFileName.empty())
    {
        throw std::invalid_argument("Target file name cannot be empty.");
    }
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

const std::string& ShrubberyCreationForm::getTarget() const
{
    return targetFileName;
}