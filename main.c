#include "minishell.h"

// t_exec *init_all(char **envp)
// {
// 	t_path *path;
//     static t_token *tokens;
//     static t_cmd   *cmd;
//     static t_exec  *exec;
// 	t_env	*env;
//     int     size;

// 	cmd = NULL;
//     env = NULL;
//     path = malloc(sizeof(t_path));
//     tokens = malloc(sizeof(t_token));
// 	if(!path || !exec || !tokens)
// 		return (NULL);
// 	size = 0;
// 	while (envp[size])
// 		size++;
// 	exec->env = &env;
// 	exec->path = path;
// 	exec->cmd = &cmd;
// 	exec->tokens = &tokens;
// 	exec->envp = envp;
//     path_function(exec, size);
// 	return(exec);
// }
void	loop_shell(t_exec *exec)
{
    char    *line;
    
	while(1)
    {
        line = readline("minishell>");
		if(line)
            add_history(line);
        exec->line = line;
		if(check_quotes(exec->line) == 0)
			(*exec->tokens) = tokenisation(line);
		exec->tmp_tokens = (*exec->tokens);
        while (exec->tmp_tokens)
        {
            if (exec->tmp_tokens->type == T_WORD)
                exec->tmp_tokens->str = expand_and_remove_quotes(exec->tmp_tokens->str, exec);
            exec->tmp_tokens = exec->tmp_tokens->next_token;
        }
        if(check_syntax((*exec->tokens), exec) == 0)
			(*exec->cmd) = parse_cmd((*exec->tokens));
        else
            continue;
        if((*exec->cmd) == NULL || (*exec->cmd)->args == NULL || (*exec->cmd)->args[0] == NULL)
            continue;
        if(check_directory(exec) == 1)
                continue;
        exec_pipe(exec);
    }
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    t_path *path;
    static t_exec  *exec;
    static t_token *tokens;
    static t_cmd   *cmd;
	t_env	*env;
    int     size;

	cmd = NULL;
    env = NULL;
    exec = malloc(sizeof(t_exec));
    path = malloc(sizeof(t_path));
    tokens = malloc(sizeof(t_token));
	if(!path || !exec || !tokens)
		return (1);
	size = 0;
	while (envp[size])
		size++;
	exec->env = &env;
	exec->path = path;
	exec->cmd = &cmd;
	exec->tokens = &tokens;
	exec->envp = envp;
    path_function(exec, size);
	loop_shell(exec);
}



