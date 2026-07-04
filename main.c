#include "minishell.h"


int main(int ac, char **av, char **envp)
{
    t_env   *env;
    t_path *path;
    t_token *tokens;
    t_cmd   *cmd;
    t_exec  *exec;
    t_token *tmp;
    char    *line;
    int     size;

    (void)av;
    (void)ac;
    
    cmd = NULL;
    path = malloc(sizeof(t_path));
    env = malloc(sizeof(t_env));
    exec = malloc(sizeof(t_exec));
    env = NULL;
    tokens = malloc(sizeof(t_token));
    size = 0;
    
    while (envp[size])
        size++;
    fill_list_env(envp, &env, size);
    get_and_cut_path(envp, path);
    get_only_access(path);
    exec->env = &env;
    exec->path = path;
    exec->cmd = &cmd;
    exec->tokens = &tokens;
    exec->envp = envp;
    while(1)
    {
        line = readline("minishell>");
		if(line)
            add_history(line);
        exec->line = line;
        if (check_quotes(exec->line) == 0)
        tokens = tokenisation(line);
        tmp = tokens;
        while (tmp)
        {
            if (tmp->type == T_WORD)
            tmp->str = expand_and_remove_quotes(tmp->str, exec);
            tmp = tmp->next_token;
        }
        cmd = NULL;
        if(check_syntax(tokens, exec) == 0)
            cmd = parse_cmd(tokens);
        if(cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
            continue;
        if(check_directory(exec) == 1)
            continue;
        exec_pipe(exec);
    }
}



