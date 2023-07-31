D_SRC			=	builtin/builtin.c builtin/run_commands.c\
				lib/ft_split.c lib/ft_strjoin.c \
				parser/env_process.c parser/lexer.c lib/utiels.c parser/parser.c \
				executor/ft_executor.c \
				main.c \
				deneme.c
OBJ			=	$(D_SRC:%.c=%.o)

CC			=	gcc
RM			=	rm -r
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
READLINE	=	-lreadline

NAME	=	minishell

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)
		
re		:	fclean all

run		:	all
			clear
			./$(NAME)

.PHONY: all re clean fclean