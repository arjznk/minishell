#include "minishell.h"

void    execute_builtins(t_exec *exec)
{
    if(ft_strcmp(exec->line, "pwd") == 0)
        ft_pwd();
    else if(ft_strncmp(exec->line, "exit", 4) == 0)
        ft_exit(exec->line);
    else if(ft_strncmp(exec->line, "echo", 4) == 0)
        ft_echo(exec->line, exec->env);
    else if (ft_strcmp(exec->line, "env") == 0)
        ft_env(exec->line, exec->env);
    else if(ft_strncmp(exec->line, "export", 6) == 0)
        ft_export(exec->line, exec->env);
    else if(ft_strncmp(exec->line, "unset", 5) == 0)
        ft_unset(exec->line, exec->env);
	else if (ft_strncmp(exec->line, "cd", 2) == 0)
        ft_cd(exec->line);
    else if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
        cmd_absolute_path(exec);
	else
        exec_pipe(exec);
        // other_cmd(exec);
}

// void    other_cmd(t_exec *exec)
// {

//     int fd[2];
//     pipe(fd);
//     tokens = malloc(sizeof(t_token));
//     int id = fork();
// 		if(id == 0)
// 		{
//             dup2(fd, fd[0]);
//             if (check_quotes(line) == 0)
//                 tokens = tokenisation(line);
//             if (check_syntax(tokens) == 0)
//                 cmds = parse_cmd(tokens);
//             size = ft_lstsize(cmds);
// 			char *newline = ft_strjoin(path->access_usr, "/");
//             char *preline = search_and_stop(tokens->str, '|');
// 			char *valid_cmd = ft_strjoin(newline, preline);
//             if(size >= 2)
//             {

//             }
//                  if(access(valid_cmd, F_OK) == 0)
//                 {
//                     execve(valid_cmd, cmds->args, envp);
//                 }    
//                 else
//                     printf("minishell: %s: command not found\n", line);
// 		}
// 		else
// 			waitpid(id, NULL, 0);
// }

void    cmd_absolute_path(t_exec *exec)
{
    char *line;
    
    line = ft_strchr_echo(exec->line, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
    else if(ft_strncmp(line, "pwd", 3) == 0)
        ft_pwd();
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line, exec->env);
    else if(ft_strncmp(line, "cd", 2) == 0)
        return;
    else if(ft_strncmp(line, "env", 3) == 0)
        ft_env(line, exec->env);
    else
        other_absolute_path(line, exec);

}

void	other_absolute_path(char *line, t_exec *exec)
{
    int id = fork();
		if(id == 0)
		{
			char *newline = ft_strjoin(exec->path->access_usr, "/");
            char *preline = search_and_stop(line, ' ');
			char *valid_cmd = ft_strjoin(newline, preline);
            if(access(valid_cmd, F_OK) == 0)
            {
                char **all;
                all = ft_split(line, ' ');
                execve(valid_cmd, all, exec->envp);
            }    
            else
				printf("minishell: %s: %s\n", line, strerror(errno));
		}
		else
			waitpid(id, NULL, 0);
}

void    exec_pipe(t_exec *exec)
{
    if ((*exec->cmd)->next_cmd->args)
    {
        int fd[2];
        pipe(fd);
        int id = fork();
        if(id == 0)
        {
            char *newline = ft_strjoin(exec->path->access_usr, "/");
            char *preline = (*exec->cmd)->args[0];
            char *valid_cmd = ft_strjoin(newline, preline);
            if(access(valid_cmd, F_OK) == 0)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                    execve(valid_cmd, (*exec->cmd)->args, exec->envp);
                }
                else
                    printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
        }
        else
        {
            int idf = fork();
            if(idf == 0)
            {
                char *newline = ft_strjoin(exec->path->access_usr, "/");
                char *preline = (*exec->cmd)->next_cmd->args[0];
                char *valid_cmd = ft_strjoin(newline, preline);
                if(access(valid_cmd, F_OK) == 0)
                    {
                        dup2(fd[0], STDIN_FILENO);
                        close(fd[0]);
                        close(fd[1]);
                        execve(valid_cmd, (*exec->cmd)->next_cmd->args, exec->envp);
                    }
                    else
                        printf("minishell: %s: command not found\n", exec->line);
            }
            close(fd[0]);
            close(fd[1]);
            waitpid(id, NULL, 0);
            waitpid(idf, NULL, 0);
        }
    }
    else
    {
        int id = fork();
        if(id == 0)
        {
            char *newline = ft_strjoin(exec->path->access_usr, "/");
            char *preline = search_and_stop((*exec->tokens)->str, ' ');
			char *valid_cmd = ft_strjoin(newline, preline);
            if(access(valid_cmd, F_OK) == 0)
                execve(valid_cmd, (*exec->cmd)->args, exec->envp); 
            else
                printf("minishell: %s: command not found\n", exec->line);
        }
        else
            waitpid(id, NULL, 0);

    }
}
