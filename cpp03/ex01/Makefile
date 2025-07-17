CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = scavtrap

SRCS = ClapTrap.cpp ScavTrap.cpp main.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re