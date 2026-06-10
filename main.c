 
#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_env   *env;
    int     size;
    t_path *path;
    t_token *tokens;

    (void)av;
    (void)ac;

    path = malloc(sizeof(t_path));
    env = malloc(sizeof(t_env));
    env = NULL;
    tokens = malloc(sizeof(t_token));
    size = 0;
    while (envp[size])
        size++;
    fill_list_env(envp, &env, size);
    get_and_cut_path(envp, path);
    get_only_access(path);
    char *line;
    while(1)
    {
		line = readline("minishell>");
		if(line)
			add_history(line);
		// execute_builtins(line, &env, path, envp);
        tokens = tokenisation(line);
        print_token(&tokens);
        check_syntax(tokens);
    }
}

