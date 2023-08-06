#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
// #include <string.h>
// #include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//#include <termios.h> // ioctl için
//#include <sys/ioctl.h>

//# define CHECK(X) ({char* __val = (X); (__val == NULL ? (perror("ERROR :")) : __val); }) // malloc erroru için
//# define CHECK_INT(X) ({int __val = (X); (__val == -1 ? (perror("ERROR :")) : __val); }) // diğer errorlar için

#define DQ '"'
#define MQ '\''

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
}	s_token;

typedef  struct t_env
{
	char			*key;
	char			*value;
	//struct t_token	*next; bu yapının linkedlist olması daha verimli bir kod sağlar, çünkü export komutu ile ekleme çıkarma yapacağız
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
	char				**redirects;
	Node				node;
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
	int flag;
}	s_minishell;

extern s_minishell gv;

s_env		*fill_env(char **envp);
void		print_env_list(s_env *env_list);
char		*ft_readline(char *str);
s_token		*ft_start(char *input);
s_token		*ft_tokens(char *input);
int			set_ctrl(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
char*		appendString(const char *dest, const char *src);
int			ft_pipe_counter(s_token *tokens);
/*LEXER*/
Node	*ft_parser(s_token *tokens);
int  	ft_char_count(const char *input, int c);
int		quote_off(const char *input);
int		ft_token_count(const char *input);
/* LIB*/
int		my_isspace(char ch);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);

/* EXECUTOR */
// void	ft_executor(Node *nodes);
void	ft_executor(Node *nodes, char **envp);

/* BUILTIN COMMANDS */
int		is_builtin(char *command);
void	run_builtin(int status, Node node);
void	run_pwd(void);
void	run_cd(Node node);
void	run_echo(Node node);
/*silinecekler*/
Node	*sahte_nodes();
// void	env_free(s_env *env_list);
#endif