#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <string>
#include <stack>
#include <deque>

template <class T, class Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
    public:
        MutantStack();
        MutantStack(const MutantStack& origin);
        MutantStack& operator=(const MutantStack& origin);
        ~MutantStack();

        // iterators
        // using typedef because you must tell the compiler that Container::iterator is a type — otherwise, it assumes you're referencing a static member or something else
        // typename is necessary because the compiler can't know that iterator is a type unless you explicitly say so with typename.
        typedef std::stack<T, Container>                    Base;
        typedef typename Container::iterator                iterator;
        typedef typename Container::const_iterator          const_iterator;
        typedef typename Container::reverse_iterator        reverse_iterator;
        typedef typename Container::const_reverse_iterator  const_reverse_iterator;

        // iterator accessors
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end()   const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend()   const;
};

template <class T, class Container>
MutantStack<T, Container>::MutantStack() : std::stack<T, Container>()
{
    // std::cout << "MutantStack default constructor called." << std::endl;
}

template <class T, class Container>
MutantStack<T, Container>::MutantStack(const MutantStack& origin) : std::stack<T, Container>(origin)
{
    // std::cout << "MutantStack copy constructor called." << std::endl;
}

template <class T, class Container>
MutantStack<T, Container>& MutantStack<T, Container>::operator =(const MutantStack& origin)
{
    // std::cout << "MutantStack copy assignment operator called." << std::endl;
    if (this != &origin)
        std::stack<T, Container>::operator=(origin);
    return *this;
}

template <class T, class Container>
MutantStack<T, Container>::~MutantStack()
{
    // std::cout << "MutantStack destructor called." << std::endl;
}

// iterators
template <class T, class Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin()
{ 
    return this->c.begin();
}

template <class T, class Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end()
{ 
    return this->c.end();
}

template <class T, class Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::begin() const
{ 
    return this->c.begin();
}

template <class T, class Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::end() const
{ 
    return this->c.end();
}

template <class T, class Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rbegin()
{ 
    return this->c.rbegin();
}

template <class T, class Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rend()
{ 
    return this->c.rend();
}

template <class T, class Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rbegin() const
{ 
    return this->c.rbegin();
}

template <class T, class Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rend() const
{ 
    return this->c.rend();
}


#endif