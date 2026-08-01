#include "minishell.h"

void 	builtins_exec(t_exec *exec)
{
	create_saved_files(exec);
	builtins_pipe(exec);
}

void	signal_exec(t_exec *exec)
{
	wait_children(exec);
	init_parent_signals();
		
}
