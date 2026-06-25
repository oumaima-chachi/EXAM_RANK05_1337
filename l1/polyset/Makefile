NAME = polyset

SRC = main.cpp array_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp tree_bag.cpp 
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f  $(NAME)

re: fclean all

.PHONY : all re clean fclean