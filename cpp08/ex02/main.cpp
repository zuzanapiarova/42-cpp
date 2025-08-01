#include "MutantStack.hpp"
#include <vector>

int main(void)
{
    // testing construction with default container type - should be deque
    MutantStack<int> stack1;   
    MutantStack<int> stack2; 

    // testing basic stack operations
    for (int i = 1; i <= 10; i++)
        stack1.push(i);
    stack1.pop();
    std::cout << "Stack1: " << stack1.size() << ", empty: " << stack1.empty() << std::endl;

    // testing construction with other container type - vector, list, ...
    MutantStack<int, std::vector<int> > vectorStack;  
    std::cout << "VectorStack: " << vectorStack.size() << ", empty: " << vectorStack.empty() << std::endl;

    // testing copy constructor
    MutantStack<int> copyStack(stack1);
    std::cout << "CopyStack: " << copyStack.size() << ", empty: " << copyStack.empty() << std::endl;

    // testing copy assignment operator
    stack2 = stack1;
    // vectorStack = stack1; // should not work - different types - vector vs deque

    // testing const stack and basic operations
    const MutantStack<int> constStack(stack1);
    std::cout << "ConstStack: " << constStack.size() << ", empty: " << constStack.empty() << std::endl << std::endl;

    // testing the basic iterator
    std::cout << "Begin: " << *(stack1.begin()) << ", end: " << *(--stack1.end()) << std::endl;

    // testing the reverse iterator
    std::cout << "Reverse begin: " << *(stack1.rbegin()) << ", reverse end: " << *(--stack1.rend()) << std::endl;

    // testing the const iterator
    std::cout << "Const Begin: " << *(constStack.begin()) << ", const end: " << *(--constStack.end()) << std::endl;

    // testing the const reverse iterator
    std::cout << "Const reverse begin: " << *(constStack.rbegin()) << ", const reverse end: " << *(--constStack.rend()) << std::endl;

    return 0;
}