#include "minishell.h"

void    execute_builtins(t_exec *exec, t_cmd *tmp)
{
    if(ft_strcmp(tmp->args[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strncmp(tmp->args[0], "exit", 4) == 0)
        ft_exit(tmp->args[0]);
    else if(ft_strncmp(tmp->args[0], "echo", 4) == 0)
        ft_echo(exec);
    else if (ft_strcmp(tmp->args[0], "env") == 0)
        ft_env(tmp->args[0], exec->env);
    else if(ft_strncmp(tmp->args[0], "export", 6) == 0)
        ft_export(tmp->args[0], exec->env);
    else if(ft_strncmp(tmp->args[0], "unset", 5) == 0)
        ft_unset(tmp->args[0], exec->env);
	else if (ft_strncmp(tmp->args[0], "cd", 2) == 0)
        ft_cd(tmp->args[0]);
    else if(ft_strncmp(tmp->args[0], "/usr/bin/", 9) == 0)
        cmd_absolute_path(exec);
}

int   is_builtins(t_exec *exec, t_cmd *tmp)
{
    (void)exec;

    if(ft_strcmp(tmp->args[0], "pwd") == 0)
        return (0);
    else if(ft_strncmp(tmp->args[0], "exit", 4) == 0)
        return (0);
    else if(ft_strncmp(tmp->args[0], "echo", 4) == 0)
        return (0);
    else if (ft_strcmp(tmp->args[0], "env") == 0)
        return (0);
    else if(ft_strncmp(tmp->args[0], "export", 6) == 0)
       return (0);
    else if(ft_strncmp(tmp->args[0], "unset", 5) == 0)
        return (0);
	else if (ft_strncmp(tmp->args[0], "cd", 2) == 0)
        return (0);
    else if(ft_strncmp(tmp->args[0], "/usr/bin/", 9) == 0)
        return (0);
    return (1);
}

void    cmd_absolute_path(t_exec *exec)
{
    char *line;
    
    line = ft_strchr_echo(exec->line, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
    else if(ft_strncmp(line, "pwd", 3) == 0)
        ft_pwd();
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(exec);
    else if(ft_strncmp(line, "cd", 2) == 0)
        return;
    else if(ft_strncmp(line, "env", 3) == 0)
        ft_env(line, exec->env);
    else
        exec_pipe(exec);
}

void    exec_pipe(t_exec *exec)
{
    t_cmd *tmp;
    int temp;

    tmp = (*exec->cmd);
    temp = -1;
    while(tmp)
    {
        int fd[2];
        pipe(fd);
        // *exec->cmd = tmp;
        if(fork() == 0)
        {
            if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
                redir_pipe_absolute(exec, tmp, fd, temp);
            else
                redir_pipe(exec, tmp, fd, temp);
        }
        temp = fd[0];
        close(fd[1]);
        tmp = tmp->next_cmd;
    }
    while(waitpid(-1, NULL, 0) > 0)
        wait(NULL);
}

void    redir_pipe(t_exec *exec, t_cmd *tmp, int fd[2], int temp)
{
    char *newline;
    char *preline;
    char *valid_cmd;
    
    newline = ft_strjoin(exec->path->access_usr, "/");
    preline = tmp->args[0];
    valid_cmd = ft_strjoin(newline, preline);
    printf("a\n");
    if(temp != -1)
    {
        if(dup2(temp, STDIN_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }    
    printf("b\n");
    if(tmp->next_cmd)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }
    printf("c\n");
    close(fd[0]);
    close(fd[1]);
    if(is_builtins(exec, tmp) == 0)
    {
        printf("d\n");
        execute_builtins(exec, tmp);
        return; 
    }
    printf("e\n");
    if(access(valid_cmd, F_OK) == 0)
    {
        printf("f\n");
        execve(valid_cmd, tmp->args, exec->envp);
        printf("g\n");
        
    }
}

void    redir_pipe_absolute(t_exec *exec, t_cmd *tmp, int fd[2], int temp)
{
	char *valid_cmd;
    
    valid_cmd = tmp->args[0];
    if(temp != -1)
    {
        if(dup2(temp, STDIN_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }  
    if(tmp->next_cmd)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            printf("minishell: %s\n", strerror(errno));
    }
    close(fd[0]);
    close(fd[1]);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, tmp->args, exec->envp);
}

/*
fd[0] = lecture
fd[1] = ecriture

faire pipe avec les builtins
faire les heredoc a part de l'exec, et localiser le heredoc dans une commande 
et l'executer avant d'executer le reste

*/

