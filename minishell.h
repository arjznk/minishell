
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

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
    char *path;
}   t_path;

//list utils
t_env				*ft_lstnew_for_env(char *value);
int					ft_lstsize(t_env *lst);
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_front(t_env **lst, t_env *new);
void				ft_lstadd_back(t_env **lst, t_env *new);

// utils functions
char *search_and_stop(char *str, char c);


void fill_list_env(char **envp, t_env **env, int size);
void	print_list(t_env **env);


// tokenisation functions
void    token_type(char *str);
t_token *new_token(char *str, t_token_type type);
char    *find_word(char *str);

#endif
