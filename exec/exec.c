#include "minishell.h"

void    execute_builtins(char *line, t_env **env, t_path *path, char **envp)
{
    if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strncmp(line, "exit", 4) == 0)
        ft_exit(line);
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line, env);
    else if (ft_strcmp(line, "env") == 0)
        ft_env(line, env);
    else if(ft_strncmp(line, "export", 6) == 0)
        ft_export(line, env);
    else if(ft_strncmp(line, "unset", 5) == 0)
        ft_unset(line, env);
	else if (ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
    else if(ft_strncmp(line, "/usr/bin/", 9) == 0)
        cmd_absolute_path(line, env, path, envp);
	else
        other_cmd(line, path, envp);
}

void    other_cmd(char *line, t_path *path, char **envp)
{
    t_cmd *cmds;
    t_token *tokens;
    int size;

    tokens = malloc(sizeof(t_token));
    int id = fork();
		if(id == 0)
		{
            if (check_quotes(line) == 0)
                tokens = tokenisation(line);
            if (check_syntax(tokens) == 0)
                cmds = parse_cmd(tokens);
            size = ft_lstsize(cmds);
            printf("size de la liste = %d\n", size);
			char *newline = ft_strjoin(path->access_usr, "/");
            printf("newline = %s\n", newline);
            // /usr/bin/
            char *preline = search_and_stop(tokens->str, '|');
            printf("preline = %s\n", preline);
            // ls
			char *valid_cmd = ft_strjoin(newline, preline);
            printf("valid cmd = %s\n", valid_cmd);
            // /usr/bin/ls

            // ls -l | wc -l
            // cmds = ls -l
            if(size >= 2)
            {

            }
                 if(access(valid_cmd, F_OK) == 0)
                {
                    // char **all;
                    // all = ft_split(, ' ');
                    execve(valid_cmd, cmds->args, envp);
                }    
                else
                    printf("minishell: %s: command not found\n", line);
		}
		else
			waitpid(id, NULL, 0);
}

void    cmd_absolute_path(char *str, t_env **env, t_path *path, char **envp)
{
    char *line = ft_strchr_echo(str, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
    else if(ft_strncmp(line, "pwd", 3) == 0)
        ft_pwd();
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line, env);
    else if(ft_strncmp(line, "cd", 2) == 0)
        return;
    else if(ft_strncmp(line, "env", 3) == 0)
        ft_env(line, env);
    else
        other_absolute_path(line, path, envp);

}

void	other_absolute_path(char *line, t_path *path, char **envp)
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
				printf("minishell: %s: %s\n", line, strerror(errno));
		}
		else
			waitpid(id, NULL, 0);
}
