D_SRC			=	builtin/builtin.c builtin/run_commands.c builtin/run_echo.c builtin/export.c builtin/run_unset.c\
				lib/ft_split.c lib/ft_strjoin.c lib/ft_strfind.c lib/utils.c lib/utils2.c lib/utils3.c lib/dolkey.c lib/ft_atoi.c\
				parser/env_process.c parser/lexer.c parser/parser.c parser/quotes.c parser/dollar.c parser/heredoc_sep.c parser/double_sep.c parser/single_sep.c parser/extra.c parser/extra2.c parser/extra3.c\
				executor/ft_executor.c executor/exec_heredoc.c executor/fd_change.c executor/contain.c executor/process_merge.c executor/ft_getenv.c\
				main.c
OBJ			=	$(D_SRC:%.c=%.o)

CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address -g
READLINE	=	-lreadline

NAME	=	minishell

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE) -g #-fsanitize=address -g

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)
		
re		:	fclean all

run		:	all
			clear
			./$(NAME)

.PHONY: all re clean fclean