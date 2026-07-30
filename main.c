/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:35:39 by rijebbar          #+#    #+#             */
/*   Updated: 2026/07/30 17:12:17 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_exec *exec)
{
	init_parent_signals();
	while (1)
	{
		if (readline_loop(exec) == 1)
			break ;
		if (init_parsing(exec) == 1)
			continue ;
		init_heredocs(exec);
		exec->tmp = *exec->cmd;
		if (check_directory(exec) == 1)
		{
			free_parsing(exec);
			continue ;
		}
        printf("cmd = %s\n", exec->tmp->args[0]);
		exec_pipe(exec);
		free_parsing(exec);
	}
}

void	init_heredocs(t_exec *exec)
{
	(*exec->cmd)->nb_heredoc = count_heredoc(*exec->tokens);
	if ((*exec->cmd)->nb_heredoc >= 1)
		(*exec->cmd)->heredocs_delims = heredocs_delims(*exec->tokens,
				(*exec->cmd)->nb_heredoc);
}

int	init_parsing(t_exec *exec)
{
	char	*tmp;

	if (check_quotes(exec->line, exec) == 0)
		(*exec->tokens) = tokenisation(exec->line);
	exec->tmp_tokens = (*exec->tokens);
	while (exec->tmp_tokens)
	{
		if (exec->tmp_tokens->type == T_WORD)
		{
			tmp = exec->tmp_tokens->str;
			exec->tmp_tokens->str = expand_and_remove_quotes(tmp, exec);
			free(tmp);
		}
		exec->tmp_tokens = exec->tmp_tokens->next_token;
	}
	if (check_syntax((*exec->tokens), exec) == 0)
		(*exec->cmd) = parse_cmd((*exec->tokens));
	else
	{
		free_parsing(exec);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	static t_exec	*exec;
	t_env			*env;
	int				size;

	(void)av;
	(void)ac;
	size = 0;
	if (ac > 1)
	{
		printf("minishell : %s : No such file or directory\n", av[1]);
		return (1);
	}
	if (!envp)
		return (1);
	exec = malloc(sizeof(t_exec));
	ft_memset(exec, 0, sizeof(t_exec));
	env = NULL;
	if (init(exec) == 1)
		return (1);
	while (envp[size])
		size++;
	exec->env = &env;
	exec->envp = envp;
	path_function(exec, size);
	loop_shell(exec);
}

int	init(t_exec *exec)
{
	static t_token		*tokens;
	static t_cmd		*cmd;
	static t_path_acces	*acces_path;
	t_path				*path;

	path = malloc(sizeof(t_path));
	if (!path || !exec)
		return (1);
	exec->tokens = &tokens;
	exec->cmd = &cmd;
	exec->path = path;
	exec->acces_path = &acces_path;
	return (0);
}
