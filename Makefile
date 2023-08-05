D_SRC			=	builtin/builtin.c builtin/run_commands.c builtin/run_echo.c\
				lib/ft_split.c lib/ft_strjoin.c \
				parser/env_process.c parser/lexer.c lib/utiels.c parser/parser.c parser/quotes.c\
				executor/ft_executor.c \
				main.c \
				deneme.c
OBJ			=	$(D_SRC:%.c=%.o)

CC			=	gcc
RM			=	rm -r
CFLAGS		=	-Wall -Wextra -Werror
READLINE	=	-lreadline

NAME	=	minishell

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) #-fsanitize=address -g

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)
		
re		:	fclean all

run		:	all
			clear
			./$(NAME)

.PHONY: all re clean fclean