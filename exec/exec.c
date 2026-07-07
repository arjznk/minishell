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
            fork_pipe(exec);
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
        cmd_error(exec);
    dup_for_pipe(exec);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, exec->tmp->args, exec->envp);
}

void    builtins_pipe(t_exec *exec)
{
	exec->saved_stdout = dup(STDOUT_FILENO);
    exec->saved_stdin = dup(STDIN_FILENO);
    if((*exec->cmd)->heredoc)
        heredocs(exec);
    else if(found_outfile(exec) == 0)
    {
        if(redirections(exec) == 1)
        {
            close_saved_files(exec);
            return;
        }
        dup2(exec->redir_fd, STDOUT_FILENO);
    }
    else if(found_infile(exec) == 0)
    {
        if(redirections(exec) == 1)
        {
            close_saved_files(exec);
            return;
        }
        dup2(exec->redir_fd, STDIN_FILENO);
    }
    else if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    dup_and_close(exec);
}

void    fork_pipe(t_exec *exec)
{
    if(found_outfile(exec) == 0 || found_infile(exec) == 0)
    {
        if (redirections(exec) == 1)
        {
            close_saved_files(exec);
            return;
        }
    }
    if(found_heredocs(exec) == 0)
        heredocs(exec);
    if(fork() == 0)
        redir_pipe(exec);
}

void    dup_for_pipe(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
    {
        dup2(exec->heredoc_fd[0], STDIN_FILENO);
        exec->old_fd = exec->heredoc_fd[0];
        close(exec->heredoc_fd[0]);
    }
    else if(found_outfile(exec) == 0)
    {
        if(redirections(exec) == 1)
            return;
        dup2(exec->redir_fd, STDOUT_FILENO);
    }
    else if(found_infile(exec) == 0)
    {
        if(redirections(exec) == 1)
            return;
        dup2(exec->redir_fd, STDIN_FILENO);
    }
    else if(exec->old_fd != -1)
        dup2(exec->old_fd, STDIN_FILENO);
    else if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    close_files(exec->fd);
}

void    close_saved_files(t_exec *exec)
{
    close(exec->saved_stdin);
    close(exec->saved_stdout);
}

void    dup_and_close(t_exec *exec)
{
    execute_builtins(exec);
    dup2(exec->saved_stdout, STDOUT_FILENO);
    dup2(exec->saved_stdin, STDIN_FILENO);
    close_saved_files(exec);
}