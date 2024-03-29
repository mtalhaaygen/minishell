/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:16:26 by tdemir            #+#    #+#             */
/*   Updated: 2023/09/15 18:16:40 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

# define DQ '"'
# define MQ '\''

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

typedef enum s_type_token
{
	TOKEN_PIPE,
	TOKEN_I,
	TOKEN_O,
	TOKEN_I_I,
	TOKEN_O_O,
	TOKEN_WORD,
	TOKEN_EOF
}	t_type_token;

typedef struct s_token
{
	int				quot_flag;
	int				fq;
	t_type_token	type;
	char			*value;
}	t_token;

typedef struct s_env
{
	int				env_count;
	char			*key;
	char			*value;
}	t_env;

typedef struct s_file
{
	t_type_token	type;
	char			*name;
}	t_file;

typedef struct s_node
{
	char		**args;
	int			arg_count;

	t_file		*infile;
	t_file		*outfile;
}	t_node;

typedef struct s_process
{
	pid_t	pid;
	int		fd[2];
}	t_process;

typedef struct s_minishell
{
	int			process_count;
	t_env		*env;
	t_node		*nodes;
	t_process	*process;
	int			flag;
	int			pid;
	char		**full;
	int			full_size;
	int			err_number;
	int			counter_num;
	int			syn_err;
	int			heredoc_count;
	int			heredoc_count_node;
	int			s_back;
}	t_minishell;

extern t_minishell	*g_va;

char		*ft_readline(char *str);
int			set_ctrl(void);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
char		*appendString(const char *dest, const char *src);

/*LEXER PARSER*/
t_token		*ft_start(char *input);
t_token		*ft_tokens(char *input);
int			ft_pipe_counter(t_token *tokens);
t_env		*fill_env(char **envp);
void		print_env_list(t_env *env_list);
t_node		*ft_parser(t_token *tokens);
int			ft_char_count(const char *input, int c);
int			quote_off(const char *input);
int			ft_token_count(const char *input);
t_token		*ft_dollar(t_token *tokens);
t_token		*ft_sep(t_token *tokens);
char		**ft_tmp_tokens(t_token *tokens);
t_token		*ft_single_sep(t_token *tokens, int i, int j, char val);
t_token		*ft_double_sep(t_token *tokens, int i, int j, char val);
void		fill_full(char **envp, int len);
t_token		*dollar_plass(t_token *tokens, int i, int j);
void		ft_wod(t_token *tokens, int i);
void		ft_change_token( char *dolval, t_token *tokens, int i, int j);
char		*ft_dolval(char *dolkey);
char		*ft_dolkey(t_token *tokens, int i, int j);
int			handle_quotes(int i, const char *str, char del);
int			ft_flag(const char *input, int start);
void		ft_token_type(t_token *tokens);
int			ft_tokens_quot_flag(char *input, int i);
void		ft_i(t_node node, int i, t_token *tokens);
void		ft_i_i(t_node node, int i, t_token *tokens);
void		ft_o(t_node node, int i, t_token *tokens);
int			ft_is_mono(t_token *tokens, int i, int j);
int			ft_is_double(t_token *tokens, int i, int j);
int			ft_eor(t_token *tokens, int i);
int			ft_pure(t_token *tokens);
void		ft_print_pipe(t_token *tokens);
void		ft_error_mesage(t_token *tokens, int i);
void		ft_single_error(t_token *tokens, int i);
void		ft_double_error(t_token *tokens, int i);
void		ft_first_pipe(t_token *tokens);
void		ft_pipe_err(void);
int			ft_pure(t_token *tokens);
int			tokencount_nq(const char *input, int i);
void		ft_ec(t_token *tokens);
void		ft_spectrum(t_token *tokens);

/* LIB */
int			my_isspace(char ch);
char		*ft_strdup(char *src);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*free_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_strncmp_signed(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strdup_dolkey(char *src);
void		free_pp(char **args);
void		ft_free_token(t_token	*tokens);
void		ft_free_node(t_node	*nodes);
int			arg_count(char **str);
int			ft_strfind(char	*str, int c);
void		ft_perror(const char *str);
int			find_full(char *new);
void		ft_syntax_error(t_node *nodes);
int			ft_atoi(const char *str);
int			ft_number(char	*str);
char		*ft_itoa(int n);
void		ft_o(t_node node, int i, t_token *tokens);
void		ft_i_i(t_node node, int i, t_token *tokens);
void		ft_i(t_node node, int i, t_token *tokens);
int			ft_envadd_counter(void);

/* EXECUTOR */
void		ft_executor(t_node *nodes);
void		ft_executor_heredoc(t_node *nodes, int th, int i, int flag);
void		exec_start(t_node *nodes);
void		exec_select(t_node *nodes);
int			is_heredoc(t_node *nodes, int index);
void		question_mark_update(char *new_value, int x);
void		is_redirection(t_node *nodes, int i);
void		ft_process_merge(int i);
void		pipe_close(void);
void		rm_heredoc(void);
int			file_access(char *filename, int flag, int f2, t_node node);
void		add_dollar_question_mark(void);
char		*ft_getenv(char *str);
char		*ft_heredoc_file(char *full);
int			ft_find_heredoc(t_node *nodes, int flag, int th, int i);
char		*ft_access(char *args);

/* BUILTIN COMMANDS */
int			is_builtin(char **args);
int			is_other_builtin(t_node node);
void		run_builtin(int status, t_node node);
void		run_other_builtin(int status, t_node node);
void		run_pwd(void);
void		run_cd(t_node node);
void		run_echo(t_node node);
void		ft_export1(t_node node);
void		ft_export2(t_node node);
void		ft_print_full(char **args);
void		run_unset(t_node node);
void		run_exit(t_node node);
void		env_update(char	*new);
void		full_update(char *new);

#endif