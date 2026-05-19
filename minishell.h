/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:42:06 by azenk             #+#    #+#             */
/*   Updated: 2026/05/19 16:25:30 by rijebbar         ###   ########.fr       */
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
}   t_token_type;

typedef struct s_token 
{
    char *str;
    char *type;
    int index;
    struct t_token *next_token;
} t_token;

typedef struct s_path
{
    char *path;
}   t_path;

//list utils
t_env				*ft_lstnew(char *value);
int					ft_lstsize(t_env *lst);
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_front(t_env **lst, t_env *new);
void				ft_lstadd_back(t_env **lst, t_env *new);

// utils functions

void fill_list_env(char **envp, t_env **env, int size);
void	print_list(t_env **env);

#endif
