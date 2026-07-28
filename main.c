/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azenk <azenk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:57:56 by azenk             #+#    #+#             */
/*   Updated: 2026/07/28 14:16:39 by azenk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_exec *exec)
{
    char    *line;

	init_parent_signals();
    while(1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            printf("exit\n");
            free_all(exec);
            break;
        }
        exec->count_line++;
        if(line)
            add_history(line);
        exec->line = line;
        if(check_quotes(exec->line) == 0)
            (*exec->tokens) = tokenisation(line);
        exec->tmp_tokens = (*exec->tokens);
        while (exec->tmp_tokens)
        {
            if (exec->tmp_tokens->type == T_WORD)
            {
                char *tmp;
                tmp = exec->tmp_tokens->str;
                exec->tmp_tokens->str = expand_and_remove_quotes(tmp, exec);
                free(tmp);
            }
            exec->tmp_tokens = exec->tmp_tokens->next_token;
        }
        if(check_syntax((*exec->tokens), exec) == 0)
            (*exec->cmd) = parse_cmd((*exec->tokens));
        else
        {
            free_parsing(exec);
            continue;
        }
        (*exec->cmd)->nb_heredoc = count_heredoc(*exec->tokens);
        // printf("nb heredocs : %d\n", count_heredoc(*exec->tokens));
        if ((*exec->cmd)->nb_heredoc >= 1)
        {
            // char **tmp = heredocs_delims(*exec->tokens, (*exec->cmd)->nb_heredoc);
            // int i = 0;
            // while (tmp[i])
            // {
            //     printf("delim = %s\n", tmp[i]);
            //     i++;
            // }
            (*exec->cmd)->heredocs_delims = heredocs_delims(*exec->tokens, (*exec->cmd)->nb_heredoc);
        }
        exec->tmp = *exec->cmd;
        if(check_directory(exec) == 1)
        {
            free_parsing(exec);
            continue;
        }
        exec_pipe(exec);
        free_parsing(exec);
    }
}

int	main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    t_path *path;
    static t_exec  *exec;
    static t_token *tokens;
    static t_cmd   *cmd;
    static t_path_acces *acces_path;
    t_env	*env;
    int     size;
    
    cmd = NULL;
    env = NULL;
    tokens = NULL;
    acces_path = NULL;
    exec = malloc(sizeof(t_exec));
    path = malloc(sizeof(t_path));
    if(!path || !exec || !envp)
        return (1);
    ft_memset(exec, 0, sizeof(t_exec)); 
    size = 0;
    while (envp[size])
        size++;
    exec->env = &env;
    exec->path = path;
    exec->cmd = &cmd;
    exec->tokens = &tokens;
    exec->envp = envp;
    exec->acces_path = &acces_path;
    path_function(exec, size);
    loop_shell(exec);
}
