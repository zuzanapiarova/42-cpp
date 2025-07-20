#ifndef BRAIN_H
# define BRAIN_H

#include <string>
#include <iostream>

class Brain
{
    private:
        std::string ideas[100];

    public:
        Brain();
        Brain(const Brain& origin);
        Brain& operator=(const Brain& origin);
        virtual ~Brain();

        std::string getIdea(int index) const;
        void setIdea(int index, const std::string& idea);
};

#endif