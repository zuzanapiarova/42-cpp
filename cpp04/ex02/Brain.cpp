#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain constructor called." << std::endl;
};

Brain::Brain(const Brain& origin)
{
    std::cout << "Brain copy constructor called." << std::endl;
    // can't assign one array to another as whole directly in C++
    // must copy the contents element by element using a loop
    for (int i = 0; i < 100; ++i)
        ideas[i] = origin.ideas[i];
}

Brain& Brain::operator=(const Brain& origin)
{
    std::cout << "Brain copy assignment operator called." << std::endl;
    if (this != &origin) {
        for (int i = 0; i < 100; ++i)
            ideas[i] = origin.ideas[i];
    }
    return *this;
};

Brain::~Brain()
{
    std::cout << "Brain destructor called." << std::endl;
};

std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100 && !ideas[index].empty())
            return ideas[index];
    return "No idea stored here";
}

void Brain::setIdea(int index, const std::string& idea)
{
    if (index >= 0 && index < 100)
        ideas[index] = idea;
}