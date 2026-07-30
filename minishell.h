/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:46:48 by azenk             #+#    #+#             */
/*   Updated: 2026/07/30 11:52:16 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 40

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next_token;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc;
	char			**heredocs_delims;
	int				nb_heredoc;
	struct s_cmd	*next_cmd;
}	t_cmd;

typedef struct s_path
{
	char	*path_env;
	char	**path_acces;
	char	*acces_usr;
}	t_path;

typedef struct s_path_acces
{
	char					*acces;
	struct s_path_acces		*next;
}	t_path_acces;

typedef struct s_exec
{
	t_env			**env;
	t_token			**tokens;
	t_path			*path;
	t_cmd			**cmd;
	t_cmd			*tmp;
	t_token			*tmp_tokens;
	t_path_acces	**acces_path;
	char			**envp;
	char			*line;
	char			*valid_cmd;
	int				status;
	int				saved_stdout;
	int				saved_stdin;
	int				fd[2];
	int				old_fd;
	int				heredoc_fd[2];
	int				redir_fd;
	char			*home;
	char			*old_pwd;
	int				count_line;
	int				save;
	char			*tmpfile;
}	t_exec;

//List utils

t_env			*ft_lstnew_for_env(char *value, t_exec *exec);
void			ft_lstadd_back(t_env **lst, t_env *new);
t_path_acces	*ft_lstnew_for_path(char *value);
void			ft_lstadd_back_path(t_path_acces **lst,
					t_path_acces *new);

//Utils functions

char			*search_and_stop(char *str, char c);
char			*str_between(char *str, char c);
int				c_strcmp(char *str, char b);
void			print_env(t_env **env);
char			*ft_strchr_echo(const char *s, int c);
int				c_strrcmp(char *str, char b);
void			sort_str(t_env **env);
char			*search_and_return(char *str, char c);
int				compar_char(int a, int b);

//Env

void			get_and_cut_path(char **envp, t_path *path);
void			fill_list_env(char **envp, t_env **env, int size,
					t_exec *exec);
void			get_only_acces(t_path *path);
char			*expand_var(char *str, int *i, char *result,
					t_exec *exec);
char			*get_env_value(char *var_name, t_env *env);
char			*get_var_name(char *str, int *i);
void			add_to_env(t_exec *exec, int i, char *temp);
void			path_function(t_exec *exec, int size);
void			fill_path_acces(t_path_acces **acces, t_exec *exec);

//Heredoc

void			heredocs(t_exec *exec);
int				found_heredocs(t_exec *exec);
void			close_heredoc_files(t_exec *exec);
void			heredoc_write(t_exec *exec, char *line);
void			loop_heredoc(t_exec *exec, int i);
void	save_readline(t_exec *exec);

//Redirections

int				redirections(t_exec *exec);
int				found_outfile(t_exec *exec);
int				found_infile(t_exec *exec);
void			redir_error(t_exec *exec);
int				redir_outfile(t_exec *exec);
int				redir_infile(t_exec *exec);

//Main 

void			loop_shell(t_exec *exec);

//Execution

void			execute_builtins(t_exec *exec);
void			create_saved_files(t_exec *exec);
void			exec_pipe(t_exec *exec);
void			init_pipe(t_exec *exec);
int				redir_pipe(t_exec *exec);
void			cmd_error(t_exec *exec);
void			close_files(t_exec *exec);
void			close_saved_files(t_exec *exec);
void			close_exec_pipe(t_exec *exec);
void			dup_and_close(t_exec *exec);
void			builtins_pipe(t_exec *exec);
void			fork_pipe(t_exec *exec);
void			dup_for_pipe(t_exec *exec);
void			exit_code(t_exec *exec);
void			exec_cmd(t_exec *exec, t_path_acces *tmp);
void			cmd_only(t_exec *exec, t_path_acces *tmp);

//Signals 
void			handle_sigint(int sig);
void			init_parent_signals(void);
void			init_child_signals(void);
void			handle_child_status(t_exec *exec, int status);
void			wait_children(t_exec *exec);
void			ignore_parent_signals(void);
void			handle_heredoc_sigint(int sig);
void			init_heredoc_signals(void);
int				heredoc_event(void);

//Builtins

int				is_builtins(t_exec *exec);
void			ft_env(t_exec *exec);
void			ft_pwd(void);
void			ft_cd(t_exec *exec);
void			cd_home(t_exec *exec);
void			cd_no_args(t_exec *exec);
void			cd_pwd(t_exec *exec);
int				exist_home(t_exec *exec);
int				check_directory(t_exec *exec);
void			ft_exit_code(char *line, char *nb, t_exec *exec);
void			ft_exit(t_exec *exec);
void			exit_return(t_exec *exec);
void			ft_echo(t_exec *exec);
void			echo_n(t_exec *exec);
void			echo(t_exec *exec);
int				check_n_valid(char *line);
void			ft_unset(t_exec *exec);
void			free_unset(t_exec *exec, t_env *prev, t_env *tmp);
void			free_path(t_exec *exec);
void			unset_var(t_exec *exec, char *key);
void			ft_export(t_exec *exec);
void			export_w_error(t_exec *exec);
void			export_only(t_exec *exec);
int				export_error(t_exec *exec);
void	        return_export(t_exec *exec, char *var);
void			exist_var(t_exec *exec, int i, t_env *tp, char *temp);

//Free 

void			free_all(t_exec *exec);
void			free_node_env(t_env **list);
void			free_tab(char **tab);
void			free_node_token(t_token **list);
void			free_node_cmd(t_cmd **list);
void			free_cmd_tokens(t_exec *exec);
void			free_node_path(t_path_acces **list);
void			free_parsing(t_exec *exec);
void			free_tmp_token(t_token *list);
void			free_for_expand(char *result, char *value,
					char *var_name);

//Tokenisation

t_token			*tokenisation(char *str);
t_token			*new_token(char *str, t_token_type type);
char			*find_word(char *str, int i);
void			add_token(t_token **token, t_token *new);
void			token_word(t_token **token, int *i, char *str);
void			token_redir_out(t_token **token, int *i, char *str);
void			token_redir_in(t_token **token, int *i, char *str);
void			token_pipe(t_token **token, int *i);
int				count_heredoc(t_token *token);
char			**heredocs_delims(t_token *token, int count);
int				check_quotes(char *str);

//Parsing 

int				check_syntax(t_token *token, t_exec *exec);
t_cmd			*new_cmd(void);
void			add_cmd(t_cmd **cmds, t_cmd *new);
t_cmd			*parse_cmd(t_token *tokens);
void			add_args(t_cmd *current, char *str);
char			*expand_and_remove_quotes(char *str, t_exec *exec);
char			*join_char(char *result, char c);

//Errors

void			syntax_error(char *token, t_exec *exec);
int				count_dots(char *cmd);
int				dot_error(t_exec *exec);

#endif