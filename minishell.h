/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:02:53 by rijebbar          #+#    #+#             */
/*   Updated: 2026/05/18 15:17:20 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

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