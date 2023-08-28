D_SRC			=	builtin/builtin.c builtin/run_commands.c builtin/run_echo.c builtin/export.c\
				lib/ft_split.c lib/ft_strjoin.c lib/put_fd.c lib/utils2.c lib/utils3.c\
				parser/env_process.c parser/lexer.c lib/utils.c parser/parser.c parser/quotes.c parser/dollar.c parser/heredoc_sep.c parser/double_sep.c parser/single_sep.c parser/extra.c parser/extra2.c\
				executor/ft_executor.c executor/exec_heredoc.c executor/fd_change.c executor/contain.c executor/process_merge.c\
				main.c
OBJ			=	$(D_SRC:%.c=%.o)

CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g
READLINE	=	-lreadline

NAME	=	minishell

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE)  #-fsanitize=address -g

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)
		
re		:	fclean all

run		:	all
			clear
			./$(NAME)

.PHONY: all re clean fclean