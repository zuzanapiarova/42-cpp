CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = brains

SRCS = Animal.cpp Dog.cpp Cat.cpp Brain.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re