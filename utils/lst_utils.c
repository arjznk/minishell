#include "minishell.h"

t_env	*ft_lstnew_for_export(char *value)
{
	t_env	*lstnew;

	lstnew = malloc(sizeof(t_env));
	if (!lstnew)
		return (NULL);
	lstnew->value = ft_strchr(value, '=');
	lstnew->variable = search_and_stop(value, ' ');
	lstnew->next = NULL;
	return (lstnew);
}