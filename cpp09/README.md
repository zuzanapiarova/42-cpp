*This project has been created as part of the 42 curriculum by zpiarova.*

# CPP09

This module consists of 3 excercises:
1. BTC - get a csv table of dates and return the price of bitcoin for that date (retrieved from another input csv table that mapas dates to prices). If date not exist, return closest sooner date.
2. RPN - Reverse polish notation - is another way of writing mathematical operations - the sign is not in the middle, but after both operands. 
3. Sorting algorithm based on Jacobsthal numbers - 

*Constraint:* Allowed to use containers from the C++ Standard Template Library (STL) only. Further, for each excercise the container used must be different. Ex02 uses 2 containers and compares their performance.

**Containers and STL:**
- The STL provides a set of common classes and interfaces for various data structures, such as vectors, lists, maps, and sets. 
- Containers are used to store data in memory, and they are part of the C++ Standard Template Library (STL).
- Each container has its own characteristics and is suitable for different use cases.

**Container types:**
1. Sequence containers: store data in a linear sequence, such as std::vector, std::list, and std::deque.
2. Associative containers: store data in a way that allows for fast retrieval based on keys, such as std::map and std::set.
3. Unordered associative containers: store data in a way that allows for fast retrieval based on keys, but do not maintain any specific order, such as std::unordered_map and std::unordered_set.
4. Container adaptors: provide a different interface for existing containers, such as std::stack, std::queue, and std::priority_queue.

## Ex00

Container type: **map** container - I store Date objects as keys and doubles as values: std::map map<Date, double>

Program (defaultly) receives a csv table of dates and prices, and a second csv table with  dates and ammounts as the parameter. 

It returns the prices of bitcoin for the dates (retrieved from another input csv table that maps dates to prices). 

If date does not exist, return closest sooner date.

Parsing rules date-price table:
- Date format: YYYY-MM-DD

Parsing rules date-amount table:
- Date format: YYYY-MM-DD
- Value: float 0-1000
- If the date from input does not exist in date-price DB, use the closest lower date in date-price DB

## Ex01

Container type: **stack** container - I store the numbers in a stack and push and pop from the top


## Ex02

Container type(s): **vector** and **deque** - I store the numbers in both containers and compare their performance. The task is to implement this algorithm for 2 different container types (advised not to do a generic function) and compare how much time it takes for both. 

