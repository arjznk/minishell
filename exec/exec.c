#include "minishell.h"

void    execute_builtins(t_exec *exec)
{
    if(ft_strcmp((*exec->cmd)->args[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp((*exec->cmd)->args[0], "exit") == 0)
        ft_exit(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "echo") == 0)
        ft_echo(exec);
    else if (ft_strcmp((*exec->cmd)->args[0], "env") == 0)
        ft_env(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "export") == 0)
        ft_export(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "unset") == 0)
        ft_unset(exec);
	else if (ft_strcmp((*exec->cmd)->args[0], "cd") == 0)
        ft_cd(exec);
    else if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        cmd_absolute_path(exec);
    else
         printf("minishell 2: %s: command not found\n", exec->line);
}

int   is_builtins(t_exec *exec)
{
    (void)exec;

    if(ft_strcmp((*exec->cmd)->args[0], "pwd") == 0)
        return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "exit") == 0)
        return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "echo") == 0)
        return (0);
    else if (ft_strcmp((*exec->cmd)->args[0], "env") == 0)
        return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "export") == 0)
       return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "unset") == 0)
        return (0);
	else if (ft_strcmp((*exec->cmd)->args[0], "cd") == 0)
        return (0);
    else if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        return (0);
    return (1);
}

void    cmd_absolute_path(t_exec *exec)
{
    char *line;
    
    line = ft_strchr_echo(exec->line, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(exec);
    else if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(line, "echo") == 0)
        ft_echo(exec);
    else if(ft_strcmp(line, "env") == 0)
        ft_env(exec);
    else
        exec_pipe(exec);
}

void    exec_pipe(t_exec *exec)
{
    int temp;

    temp = -1;
    while((*exec->cmd))
    {
        int fd[2];
        pipe(fd);
        if(fork() == 0)
        {
            if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
                redir_pipe_absolute(exec, fd, temp);
            else
                redir_pipe(exec, fd, temp);
        }
        temp = fd[0];
        close(fd[1]);
        (*exec->cmd) =(*exec->cmd)->next_cmd; 
    }
    while(waitpid(-1, NULL, 0) > 0)
        wait(NULL);
}

void    redir_pipe(t_exec *exec, int fd[2], int temp)
{
    char *newline;
    char *preline;
    char *valid_cmd;
    
    newline = ft_strjoin(exec->path->access_usr, "/");
    preline = (*exec->cmd)->args[0];
    valid_cmd = ft_strjoin(newline, preline);
    if(temp != -1)
    {
        if(dup2(temp, STDIN_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }    
    if((*exec->cmd)->next_cmd)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }
    close(fd[0]);
    close(fd[1]);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, (*exec->cmd)->args, exec->envp);
    else
        printf("minishell 1: %s: command not found\n", exec->line);
}

void    redir_pipe_absolute(t_exec *exec, int fd[2], int temp)
{
	char *valid_cmd;
    
    valid_cmd = (*exec->cmd)->args[0];
    if(temp != -1)
    {
        if(dup2(temp, STDIN_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }  
    if((*exec->cmd)->next_cmd)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }
    close(fd[0]);
    close(fd[1]);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, (*exec->cmd)->args, exec->envp);
    else
        printf("minishell 1: %s: command not found\n", exec->line);
}

/*
fd[0] = lecture
fd[1] = ecriture

faire pipe avec les builtins
faire les heredoc a part de l'exec, et localiser le heredoc dans une commande 
et l'executer avant d'executer le reste

*/

