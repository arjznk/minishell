#include "minishell.h"

void    execute_builtins(char *line, t_env **env, t_path *path, char **envp)
{
    if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strncmp(line, "exit", 4) == 0)
        ft_exit(line);
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line);
    else if (ft_strcmp(line, "env") == 0)
        ft_env(line, env);
    else if(ft_strncmp(line, "export", 6) == 0)
        ft_export(line, env);
    else if(ft_strncmp(line, "unset", 5) == 0)
        ft_unset(line, env);
	else if (ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
	else
        other_cmd(line, path, envp);
}

void    other_cmd(char *line, t_path *path, char **envp)
{
    int id = fork();
		if(id == 0)
		{
			char *newline = ft_strjoin(path->access_usr, "/");
            char *preline = search_and_stop(line, ' ');
			char *valid_cmd = ft_strjoin(newline, preline);
            if(access(valid_cmd, F_OK) == 0)
            {
                char **all;
                all = ft_split(line, ' ');
                execve(valid_cmd, all, envp);

            }    
            else
                printf("minishell: %s: command not found\n", line);
		}
		else
			waitpid(id, NULL, 0);
}
