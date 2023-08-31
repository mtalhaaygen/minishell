#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
// #include <string.h>
#include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//#include <termios.h> // ioctl için
#include <sys/ioctl.h>

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
	int quot_flag;
	int fq;
	TokenType		type;
	char			*value;
}	s_token;

typedef  struct t_env
{
	int				env_count;
	char			*key;
	char			*value;
}	s_env;

// typedef  struct t_newenv
// {
// 	char		**full;
// 	int			full_size;
// }	s_newenv;

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
}	s_process;

typedef struct t_minishell
{
	int			process_count;	// ! process count
	s_env		*env;			// ? tüm envler
	Node		*nodes;			// TODO: tüm nodelar
	s_process	*process;		// ** tüm processler
	int			flag;
	int			pid;
	char		**full;
	int			full_size;
	int			err_number;
}	s_minishell;

extern s_minishell *g_va;

char		*ft_readline(char *str);
int			set_ctrl(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
char		*appendString(const char *dest, const char *src);

/*LEXER PARSER*/
s_token		*ft_start(char *input);
s_token		*ft_tokens(char *input);
int			ft_pipe_counter(s_token *tokens);
s_env		*fill_env(char **envp);
void		print_env_list(s_env *env_list);
Node		*ft_parser(s_token *tokens);
int			ft_char_count(const char *input, int c);
int			quote_off(const char *input);
int			ft_token_count(const char *input);
s_token		*ft_dollar(s_token *tokens);
s_token		*ft_sep(s_token *tokens);
char		**ft_tmp_tokens(s_token *tokens);
s_token		*ft_single_sep(s_token *tokens, int i, int j, char val);
s_token		*ft_double_sep(s_token *tokens, int i, int j, char val);
void		fill_full(char **envp, int len);
s_token		*dollar_plass(s_token *tokens, int i, int j);
void		ft_wod(s_token *tokens, int i);
void		ft_change_token( char *dolval, s_token *tokens, int i, int j);
char		*ft_dolval(char *dolkey);
char		*ft_dolkey(s_token *tokens, int i, int j);
int			handle_quotes(int i, const char *str, char del);
int			ft_flag(const char *input, int start);
void		ft_token_type(s_token *tokens);
int			ft_tokens_quot_flag(char *input, int i);
void		ft_i(Node node, int i, s_token *tokens);
void		ft_i_i(Node node, int i, s_token *tokens);
void		ft_o(Node node, int i, s_token *tokens);
/* LIB*/
int			my_isspace(char ch);
char		*ft_strdup(char *src);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*free_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strncmp_signed(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strdup_dolkey(char *src);
void		insertionSort(char** arr, int size);
void		free_pp(char **args);
int			arg_count(char **str);
int			ft_strfind(char	*str, int c);
char		**protect(void);
void		ft_perror(const char *str);
int			find_full(char *new);
void		ft_syntax_error(Node *nodes);

/* EXECUTOR */
void		ft_executor(Node *nodes, char **envp);
void		ft_executor_heredoc(Node *nodes, const int th, const int i, int flag);
void		exec_start(Node *nodes, char **envp);
void		exec_select(Node *nodes, char **envp);
int			is_heredoc(Node *nodes, int index);
// int			contain_i(char **commands);
// int			contain_ii(char **commands);
// int			contain_o(char **commands);
void		is_redirection(Node *nodes, int i);
void		ft_process_merge(int i);
void		pipe_close(void);
void		rm_heredoc(void);
int			file_access(char *filename, int flag);

/* BUILTIN COMMANDS */
int			is_builtin(char **args);
int			is_other_builtin(Node node);
void		run_builtin(int status, Node node);
void		run_other_builtin(int status, Node node);
void		run_pwd(void);
void		run_cd(Node node);
void		run_echo(Node node);
void		ft_export1(Node node);
void		ft_export2(Node node);
void		ft_print_full(char **args);
void		run_unset(Node node);

#endif