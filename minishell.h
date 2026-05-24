
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
t_env				*ft_lstnew_for_env(char *value);
int					ft_lstsize(t_env *lst);
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_front(t_env **lst, t_env *new);
void				ft_lstadd_back(t_env **lst, t_env *new);

// utils functions
char *search_and_stop(char *str, char c);
void	print_list(t_env **env);
char    *str_between(char *str, char c);
int c_strcmp(char *str, char b);
char    *ft_strchr_between(char *s, char c);

//env   
void    get_and_cut_path(char **envp, t_path *path);
void fill_list_env(char **envp, t_env **env, int size);
void    get_only_access(t_path *path);

//built-in
void    ft_pwd(char *str);
void    ft_cd(char *str, t_path *path);
void    ft_exit(char *str);
void    ft_echo(char *str);
void    echo_for_exit(char *str, int nb);

//free
void	free_tab(long *tab);
void	free_node(t_list **list);


// tokenisation functions
void    token_type(char *str);
t_token *new_token(char *str, t_token_type type);
char    *find_word(char *str);
void    add_token(t_token **token, t_token *new);

#endif
