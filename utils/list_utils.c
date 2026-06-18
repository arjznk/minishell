#include "minishell.h"

void ft_lstdelone(t_env *lst, void (*del)(void*))
{
    if(!lst || !del)
    del(lst->variable);
    free(lst);
}
