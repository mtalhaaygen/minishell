#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

//#include <termios.h> // ioctl için
//#include <sys/ioctl.h>

//# define CHECK(X) ({char* __val = (X); (__val == NULL ? (perror("ERROR :")) : __val); }) // malloc erroru için
//# define CHECK_INT(X) ({int __val = (X); (__val == -1 ? (perror("ERROR :")) : __val); }) // diğer errorlar için

enum e_builtin_types
{
	CD = 1,
	ENV,
	PWD,
	EXIT,
	ECHO,
	UNSET,
	EXPORT
};

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
	TokenType		type;
	char			*value;
	//struct t_token	*next; bu yapının linkedlist olması daha verimli bir kod sağlar, çünkü export komutu ile ekleme çıkarma yapacağız
}	s_token;

typedef  struct t_env
{
	char			*key;
	char			*value;
}	s_env;

typedef struct t_file //DENEYSEL
{
	TokenType		type;
	char			*name;
}	s_file;

typedef struct Node
{
	char		**args;
	int			arg_count;

	s_file		*infile;
	s_file		*outfile;
}				Node;


typedef struct t_process
{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	char				**execute;
	char				**redirects;
	struct t_process	*prev;
	struct t_process	*next;
}	s_process;

typedef struct t_minishell
{
	int			parent_pid;		// main process pid
	int			process_count;	// process count
	char		**paths;		// bunun yerine s_file struct yapısı olabilir
	s_env		*env;			// tüm envler
	Node		*nodes;			// tüm nodelar
	s_process	*process;		// tüm processler
}	s_minishell;

extern s_minishell	g_ms;

s_env		*fill_env(char **envp);
void		print_env_list(s_env *env_list);
char		*ft_readline(char *str);
s_token		*ft_start(char *input);
s_token		*ft_tokens(char *input);
int			my_isspace(char ch);
int			set_ctrl(void);
Node		*ft_parser(s_token *tokens);
void		sigint_handler(int signum);
char*		appendString(const char *dest, const char *src);
void		sigquit_handler(int signum);

/* LIB*/
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* EXECUTOR */
int		ft_executor(Node *nodes);
int		ft_history(char *line);

/* BUILTIN COMMANDS */
int		is_builtin(char *command);
void	run_builtin(int status);

/*silinecekler*/
Node	*sahte_nodes();
// void	env_free(s_env *env_list);
#endif