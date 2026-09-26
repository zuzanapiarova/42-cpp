#include "PmergeMe.hpp"
#include <cstdlib>
#include <cerrno>
#include <climits>

// TODO:
// 1. handle duplicates - now errors if there are any
// 2. prevent receiving negative values and wrapping
// 3. initialize containers with default sizes so it is faster?
// 4. add second container type and optimize for it 
// 5. add measuring time

static bool parsePositiveInt(const char* str, int& result)
{
	char* end;

	if (str == NULL || *str == '\0')
		return false;

	errno = 0;
	long value = std::strtol(str, &end, 10);

	if (errno == ERANGE || *end != '\0')
		return false;

	if (value < 0 || value > INT_MAX)
		return false;

	result = static_cast<int>(value);
	return true;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: not enough numbers provided." << std::endl;
		return 1;
	}

	std::vector<int> vectorContainer;
	std::deque<int> dequeContainer;

    // populate both containers
	for (int i = 1; i < argc; ++i)
	{
		int value;
        
		if (!parsePositiveInt(argv[i], value))
		{
			std::cerr << "Error: invalid number: " << argv[i] << ". Aborting." << std::endl;
			return 1;
		}
		if (std::find(vectorContainer.begin(), vectorContainer.end(), value) != vectorContainer.end()) {
			std::cerr << "Error: duplicates: " << argv[i] << ". Aborting." << std::endl;
			return 1;
		}
		vectorContainer.push_back(value);
		dequeContainer.push_back(value);
	}

	// create class and sort and print results
	PmergeMe pmergeMe(vectorContainer, dequeContainer);
	pmergeMe.sort();

	return 0;
}