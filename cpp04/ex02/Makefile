CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = abstract_animals

SRCS = Animal.cpp Dog.cpp Cat.cpp Brain.cpp main.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re