NAME = irc

HEADER = $(shell find . -name "*.hpp")

LIST = $(shell find . -name "*.cpp")

FLAGS = -Wall -Wextra -Werror

OBJ = $(LIST:.cpp=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.cpp $(HEADER)
	clang++ -g -I includes/ $(FLAGS) -c $< -o $@

${NAME} : $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

run : all
	./irc 6667 123

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all