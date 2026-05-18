/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:42:06 by azenk             #+#    #+#             */
/*   Updated: 2026/05/18 15:55:36 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

typedef struct t_env
{
    char *key;
    char *content;
    struct t_env *next;
    
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
    struct s_token *next_token;
} t_token;

#endif