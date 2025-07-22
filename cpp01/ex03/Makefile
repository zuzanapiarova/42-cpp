CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = violence

SRCS = Weapon.cpp HumanA.cpp HumanB.cpp main.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re