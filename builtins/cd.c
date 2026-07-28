#include "minishell.h"

void	ft_cd(t_exec *exec)
{
	if(ft_strcmp(exec->tmp->args[0], "cd") != 0)
	{
		printf("minishell: %s: command not found\n", exec->tmp->args[0]);
		exec->status = 127;
		return;
	}
	if(!exec->tmp->args[1])
		return(cd_no_args(exec));
	if(ft_strcmp(exec->tmp->args[1], "-") == 0)
		return(cd_home(exec));
	cd_pwd(exec);
}

void	cd_no_args(t_exec *exec)
{
	if(exist_home(exec) == 1)
	{
		printf("minishell: cd: HOME not set\n");
		exec->status = 1;
		return;
	}
	chdir(exec->home);
}

void	cd_pwd(t_exec *exec)
{
	char	buf[BUFFER_SIZE];

	getcwd(buf, BUFFER_SIZE);
	if(chdir(exec->tmp->args[1]) == 0)
		exec->old_pwd = ft_strdup(buf);
	else if(chdir(exec->tmp->args[1]) == -1)
	{
		printf("minishell: cd: %s: %s\n", exec->tmp->args[1], strerror(errno));
		exec->status = 1;
	}
}

int		exist_home(t_exec *exec)
{
	t_env *tmp;

	tmp = (*exec->env);
	while(tmp)
	{
		if(ft_strcmp(tmp->variable, "HOME") == 0)
			return (0);
		else if(tmp->next == NULL)
			return (1);
		tmp =  tmp->next;
	}
	return (0);

}

void	cd_home(t_exec *exec)
{
	chdir(exec->old_pwd);
	printf("%s\n", exec->old_pwd);

}


