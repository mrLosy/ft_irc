NAME		= irc

SRCS		= $(shell find . -name "*.cpp")

OBJS		= $(addprefix $(BIN_DIR), $(SRCS:.cpp=.o))

CXX			= clang++

RM			= rm -f

CXXFLAGS	= -Wall -Wextra -Werror -I. -Wshadow -Wno-shadow -std=c++98 -g3

INCLUDES	= $(shell find . -name "*.hpp")

.PHONY:		all clean fclean re test

all:		
		$(MAKE) $(NAME) $(BIN) -j 12
		# когда будешь дома делать измени число после j на 4, хз сколько потоков у тебя на компе, но думаю 4 точно есть или удали просто))

$(BIN_DIR)%.o: $(SRCS_DIR)%.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#-include $(OBJSRCS:.o=.d)

$(NAME):	$(OBJS)
			@echo "\033[0;33m[ex00 compilation...]"
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
			@echo "\033[0;32m[Done!]"

clean:
		@echo "\033[0;31m[Deleting *.0 files...]"
		#rm ./*.d
		$(RM) $(OBJS)

fclean:	clean
		@echo "\033[0;31m[Deleting all files...]"
		$(RM) $(NAME)

re:		fclean all

.SILENT: