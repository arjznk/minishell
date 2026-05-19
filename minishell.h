/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:42:06 by azenk             #+#    #+#             */
/*   Updated: 2026/05/19 16:42:07 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef enum s_token_type 
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
    char *type;
    int index;
    struct t_token *next_token;
} t_token;

//list utils
t_env				*ft_lstnew(char *value);
int					ft_lstsize(t_env *lst);
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_front(t_env **lst, t_env *new);
void				ft_lstadd_back(t_env **lst, t_env *new);

void fill_list_env(char **envp, t_env **env, int size);
void	print_list(t_env **env);

#endif
