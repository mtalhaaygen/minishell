#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <termios.h> // ioctl için
#include <sys/ioctl.h>

typedef enum
{
	TOKEN_PIPE,
	TOKEN_I,
	TOKEN_O,
	TOKEN_I_I,
	TOKEN_O_O,
	TOKEN_WORD,
	TOKEN_EOF
}				TokenType;

typedef struct t_token
{
	TokenType	type;
	char		*value;
}				s_token;

typedef  struct t_env
{
    char *key;
	char *value;
}   s_env;

//**

typedef struct t_file //DENEYSEL
{
	TokenType		type;
	char			*name;
}				s_file;

typedef struct Node
{
	char		**args;
	int			arg_count;

	s_file		*infile;
	s_file		*outfile;
}				Node;


s_env	*fill_env(char **envp);
char	**ft_split(char const *s, char c);
void	print_env_list(s_env *env_list);
char	*ft_readline(char *str);
char	*ft_strdup(char *src);
s_token	*ft_start(char *input);
void	ft_tokens(char *input);
int		my_isspace(char ch);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		set_ctrl(void);
void sigint_handler(int signum);
void sigquit_handler(int signum);
// void	env_free(s_env *env_list);
#endif