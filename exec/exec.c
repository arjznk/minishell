#include "minishell.h"

void    exec_pipe(t_exec *exec)
{
    exec->old_fd = -1;
    exec->status = -1;
    exec->tmp = (*exec->cmd);
    while(exec->tmp)
    {
        pipe(exec->fd);
        *exec->cmd = exec->tmp;
        if(absolute_path(exec) == 0)
            exec_absolute_path(exec);
        else if(is_builtins(exec) == 0)
            builtins_pipe(exec);
        else
            fork_pipe_heredocs(exec);
        exec->old_fd = exec->fd[0];
        close(exec->fd[1]);
        exec->tmp = exec->tmp->next_cmd; 
    }
    while(waitpid(-1, &exec->status, 0) > 0)
        exec->status = WEXITSTATUS(exec->status);
}

void    redir_pipe(t_exec *exec)
{
    char *newline;
    char *valid_cmd;
    
    *exec->cmd = exec->tmp;
    if(ft_strncmp(exec->tmp->args[0], "/usr/bin/", 9) != 0)
    {
        newline = ft_strjoin(exec->path->access_usr, "/");
        valid_cmd = ft_strjoin(newline, exec->tmp->args[0]);
    }
    else
        valid_cmd = exec->tmp->args[0];
    if(access(valid_cmd, F_OK) != 0)
    {
        (dup2(exec->old_fd, STDIN_FILENO));
        cmd_error(exec);
    }
    dup_for_pipe(exec);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, exec->tmp->args, exec->envp);
    else
        cmd_error(exec);
}

void    redir_pipe_absolute(t_exec *exec)
{
	char *valid_cmd;
    
    valid_cmd = exec->tmp->args[0];
    *exec->cmd = exec->tmp;
    if(fork() == 0)
    {
        if(access(valid_cmd, F_OK) != 0)
        {
            (dup2(exec->old_fd, STDIN_FILENO));
            cmd_error(exec);
        }
        if(exec->old_fd != -1)
            dup2(exec->old_fd, STDIN_FILENO);
        if(exec->tmp->next_cmd)
            dup2(exec->fd[1], STDOUT_FILENO);
        close_files(exec->fd);
        if(access(valid_cmd, F_OK) == 0)
            execve(valid_cmd, exec->tmp->args, exec->envp);
        else
            cmd_error(exec);
    }
}

void    cmd_error(t_exec *exec)
{
    printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
    exec->status = 127;
    exit(127);
}

void    close_files(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

void    builtins_pipe(t_exec *exec)
{
    exec->saved_stdout = dup(STDOUT_FILENO);
    if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    execute_builtins(exec);
    dup2(exec->saved_stdout, STDOUT_FILENO);
    close(exec->saved_stdout); 
}

void    fork_pipe_heredocs(t_exec *exec)
{
    if(found_heredocs(exec) == 0)
        heredocs(exec);
    if(fork() == 0)
        redir_pipe(exec);
}

int    absolute_path(t_exec *exec)
{
    if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        return 0;
    return 1;
}

void    is_absolute_path(t_exec *exec)
{
    char *line;

    line = ft_strchr_echo((*exec->cmd)->args[0], 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(exec);
    else if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(line, "echo") == 0)
        ft_echo(exec);
    else if(ft_strcmp(line, "env") == 0)
        ft_env(exec);
    else if(ft_strcmp(line, "export") == 0 || ft_strcmp(line, "unset") == 0 || ft_strcmp(line, "exit") == 0)
    {
        printf("minishell: %s: No such file or directory\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
    else
        redir_pipe_absolute(exec);
}

void    exec_absolute_path(t_exec *exec)
{
    exec->saved_stdout = dup(STDOUT_FILENO);
    if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    is_absolute_path(exec);
    dup2(exec->saved_stdout, STDOUT_FILENO);
    close(exec->saved_stdout); 
}

void    dup_for_pipe(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
    {
        dup2(exec->heredoc_fd[0], STDIN_FILENO);
        exec->old_fd = exec->heredoc_fd[0];
        close(exec->heredoc_fd[0]);
    }
    if(exec->old_fd != -1)
        dup2(exec->old_fd, STDIN_FILENO);
    if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    close_files(exec->fd);
}
