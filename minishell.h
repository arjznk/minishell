
#ifndef MINISHELL_H
# define MINISHELL_H

#define BUFFER_SIZE 40

# include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
    
}t_env;

typedef enum e_token_type 
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_APPEND,
    T_HEREDOC,
}   t_token_type;

typedef struct s_token 
{
    char *str;
    t_token_type type;
    struct s_token *next_token;
} t_token;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int append;
    char *heredoc;
    struct s_cmd *next_cmd;

} t_cmd;

typedef struct s_path
{
    char *path_env;
    char **path_access;
    char *access_usr;
}   t_path;

typedef struct s_path_access
{
    char *acces;
    struct s_path_access *next;
}   t_path_access;

typedef struct s_exec
{
    t_env **env;
    t_token **tokens;
    t_path *path;
    t_cmd **cmd;
    t_cmd   *tmp;
    char **envp;
    char *line;
    char *valid_cmd;
    int status;
    int saved_stdout;
    int fd[2];
    int old_fd;
} t_exec;

//list utils
t_env   *ft_lstnew_for_env(char *value);
int     ft_lstsize(t_cmd *lst);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstadd_back(t_env **lst, t_env *new);

// utils functions
char    *search_and_stop(char *str, char c);
void	print_token(t_token **token);
void    print_cmds(t_cmd *cmds);
char    *str_between(char *str, char c);
int     c_strcmp(char *str, char b);
void	print_env(t_env **env);
char	*ft_strchr_echo(const char *s, int c);
int     c_strrcmp(char *str, char b);
void    sort_str(t_env **env);
char	*search_and_return(char *str, char c);

//env   
void    get_and_cut_path(char **envp, t_path *path);
void    fill_list_env(char **envp, t_env **env, int size);
void    get_only_access(t_path *path);
char    *expand_var2(char *str, int *i, char *result, t_exec *exec);
char    *get_env_value(char *var_name, t_env *env);
char    *get_var_name(char *str, int *i);
//exec
void    execute_builtins(t_exec *exec);
void    exec_absolute_path(t_exec *exec);
void    is_absolute_path(t_exec *exec);
void    exec_pipe(t_exec *exec);
void    redir_pipe(t_exec *exec);
void    redir_pipe_absolute(t_exec *exec);
void    cmd_error(t_exec *exec);
void    close_files(int fd[2]);
void    heredocs(t_exec *exec);
int     found_heredocs(t_exec *exec);
void    builtins_pipe(t_exec *exec);
void    fork_pipe_heredocs(t_exec *exec);
int     absolute_path(t_exec *exec);

//expand
// void    expand_var(t_exec *exec);
void    exit_code(t_exec *exec);

//signal
void    set_sig_childen(void);
void    set_sig_parent(void);

//built-in
int     is_builtins(t_exec *exec);
void    ft_env(t_exec *exec);
void    ft_pwd();
void    ft_cd(t_exec *exec);
void    ft_exit_code(char *line, char *nb);
void    ft_exit(t_exec *exec);
void    ft_echo(t_exec *exec);
void    echo_n(t_exec *exec);
void    echo(t_exec *exec);
int     check_n_valid(char *line);
void    ft_unset(t_exec *exec);
void    ft_export(t_exec *exec);
void    export_w_error(t_exec *exec, t_env *newnode);
void    export_only(t_exec *exec);

//free
void 	free_all(char *line, t_path *path, t_env **env);
void	free_tab(long *tab);
void	free_node_env(t_env **list);
void	free_node_path(t_path_access **list);

// tokenisation functions
t_token    *tokenisation(char *str);
t_token      *new_token(char *str, t_token_type type);
char    *find_word(char *str, int i);
void    add_token(t_token **token, t_token *new);
void    token_word(t_token **token, int *i, char *str);
void    token_redir_out(t_token **token, int *i, char *str);
void    token_redir_in(t_token **token, int *i, char *str);
void    token_pipe(t_token **token, int *i);
// char    *delete_quotes(char *str);
int check_quotes(char *str);

// parsing functions
int    check_syntax(t_token *token);
t_cmd   *new_cmd (void);
void    add_cmd(t_cmd **cmds, t_cmd *new);
t_cmd   *parse_cmd(t_token *tokens);
void   add_args(t_cmd *current, char *str);
char    *expand_and_remove_quotes(char *str, t_exec *exec);
char    *join_char(char *result, char c);
#endif
