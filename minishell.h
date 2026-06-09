
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

//list utils
t_env   *ft_lstnew_for_env(char *value);
int     ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew_for_export(char *value);

// utils functions
char    *search_and_stop(char *str, char c);
void	print_list(t_env **env);
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

//exec
void    execute_builtins(char *line, t_env **env, t_path *path, char **envp);
void    other_cmd(char *line, t_path *path, char **envp);
void    cmd_absolute_path(char *str, t_env **env, t_path *path, char **envp);
void	other_absolute_path(char *line, t_path *path, char **envp);

//built-in
void    ft_env(char *str, t_env **env);
void    ft_pwd();
void    ft_cd(char *str);
void    ft_exit_code(char *line, char *nb);
void    ft_exit(char *str);
void    ft_echo(char *str);
void    echo_n(char *str);
void    echo_quote(char *str);
void    ft_unset(char *str, t_env **env);
void	unset_env(char *line, t_env **env);
void    ft_export(char *str, t_env **env);
void    export_w_error(char **all, t_env **env, t_env *newnode);
void    export_only(t_env **env);

//free
void 	free_all(char *line, t_path *path, t_env **env);
void	free_tab(long *tab);
void	free_node_env(t_env **list);
void	free_node_path(t_path_access **list);

// tokenisation functions
t_token    *token_type(char *str);
t_token *new_token(char *str, t_token_type type);
char    *find_word(char *str, int i);
void    add_token(t_token **token, t_token *new);
void    token_word(t_token **token, int *i, char *str);
void    token_redir_out(t_token **token, int *i, char *str);
void    token_redir_in(t_token **token, int *i, char *str);
void    token_pipe(t_token **token, int *i);

// parsing functions
void    check_syntax(t_token *token);
#endif
