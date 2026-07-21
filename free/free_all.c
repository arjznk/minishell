#include "minishell.h"

void	free_all(t_exec *exec)
{
	if (exec->env)
		free_node_env(exec->env);
	if(exec->path)
		free_tab(exec->path->path_access);
	if(exec->line)
		free(exec->line);
	if(exec->cmd)
		free_node_cmd(exec->cmd);
	if(exec->tokens)
		free_node_token(exec->tokens);
}

void	free_cmd_tokens(t_exec *exec)
{
	if(exec->line)
		free(exec->line);
	if(exec->tokens && (*exec->tokens))
		free_node_token(exec->tokens);
	if(exec->cmd || (*exec->cmd))
		free_node_cmd(exec->cmd);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_node_env(t_env **list)
{
	t_env	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->variable);
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_node_token(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next_token;
		free(token->str);
		free(token);
		token = next;
	}
}

void	free_node_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next_cmd;
		free_args(cmd->args);
		free(cmd);
		cmd = next;
	}
}
