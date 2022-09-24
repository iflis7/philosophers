NAME = philo

SRCS_PATH = src/

CC = gcc
CFLAGS =  -Wall -Werror -Wextra -fsanitize=thread -g 
RM = rm -f

SRCS_FILES = philo.c init.c check_args.c logs.c utils.c threading.c routine.c moves.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)


all: 	$(NAME)
	@echo "BOOM 💥💥💥💥💥 $(NAME) Compiled! 💯 $(DEFAULT)"

$(NAME): $(OBJS)
	-@$(CC) $(CFLAGS) -o $@ $^ 
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@$(RM) $(OBJS) 
	@echo "$(YELLOW)Object files deleted!$(DEFAULT)💯"

fclean:	clean
	@$(RM) $(NAME) 

re:		fclean all

git:
	@git add .
	@git commit -m "$(message)"
	@git push
	@echo "\n$(GREEN)$(message) Committed!$(DEFAULT)💯"

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
message = "Commit Message By Default On $(shell date "+%d %B %T")"

.PHONY:	all clean libft fclean re message
