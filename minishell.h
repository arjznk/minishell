
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
    char *args;
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


//list utils
t_env   *ft_lstnew_for_env(char *value);
int     ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstadd_back(t_env **lst, t_env *new);

// utils functions
char    *search_and_stop(char *str, char c);
void	print_list(t_token **token);
char    *str_between(char *str, char c);
int     c_strcmp(char *str, char b);
int     is_letter(char *str);
void	print_env(t_env **env);
char	*ft_strchr_echo(const char *s, int c);
int     c_strrcmp(char *str, char b);

//env   
void    get_and_cut_path(char **envp, t_path *path);
void    fill_list_env(char **envp, t_env **env, int size);
void    get_only_access(t_path *path);

//built-in
void    execute_builtins(char *line, t_env **env);
void    ft_pwd(char *str);
void    ft_cd(char *str, t_path *path);
void    ft_exit_code(char *line, char *nb);
void    ft_exit(char *str);
void    ft_echo(char *str);
void    ft_env(char *str, t_env **env);
void    ft_echo_n(char *str);
void    echo_simple_quote(char *str);
void    ft_unset(char *str, t_env **env);
void    unset_if_first(t_env **env, t_env *tmp, t_env *to_free);
void    unset_if_middle(t_env *tmp, t_env *prev, t_env *to_free);
void    ft_export(char *str);

//free
void	free_tab(long *tab);
void	free_node(t_env **list);

// tokenisation functions
t_token    *tokenisation(char *str);
t_token *new_token(char *str, t_token_type type);
char    *find_word(char *str, int i);
void    add_token(t_token **token, t_token *new);
void    token_word(t_token **token, int *i, char *str);
void    token_redir_out(t_token **token, int *i, char *str);
void    token_redir_in(t_token **token, int *i, char *str);
void    token_pipe(t_token **token, int *i);


// parsing functions
void    check_syntax(t_token *token);
t_cmd   *new_cmd (void);
void    add_cmd(t_cmd **cmds, t_cmd *new);
#endif
