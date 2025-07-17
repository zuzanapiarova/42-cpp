CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = diamondtrap

SRCS = ClapTrap.cpp ScavTrap.cpp FragTrap.cpp DiamondTrap.cpp main.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re