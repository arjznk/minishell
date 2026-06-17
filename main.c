 
#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_env   *env;
    int     size;
    t_path *path;
    t_token *tokens;
    t_cmd   *cmd;
    t_exec  *exec;

    (void)av;
    (void)ac;

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
    char *line;
    exec->env = &env;
    exec->path = path;
    exec->cmd = &cmd;
    exec->tokens = &tokens;
    exec->envp = envp;
    t_cmd *tmp;
    tmp =  (*exec->cmd);
    while(1)
    {
		line = readline("minishell>");
		if(line)
			add_history(line);
        exec->line = line;
        if (check_quotes(exec->line) == 0)
            tokens = tokenisation(line);
        if(check_syntax(tokens) == 0)
            cmd = parse_cmd(tokens);
        exec_pipe(exec);
        execute_builtins(exec, tmp);
    }
}
