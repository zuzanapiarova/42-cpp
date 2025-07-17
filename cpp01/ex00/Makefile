CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = zombie

SRCS = Zombie.cpp NewZombie.cpp RandomChump.cpp main.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re