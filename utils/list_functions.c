
#include "minishell.h"

t_env	*ft_lstnew_for_env(char *value)
{
	t_env	*lstnew;
	char *tmp;

	lstnew = malloc(sizeof(t_env));
	if (!lstnew)
		return (NULL);
	if(ft_strchr(value, '=') != NULL)
	{
		tmp = ft_strchr(value, '=');
		lstnew->value = ft_strdup(tmp);
		lstnew->variable = search_and_stop(value, '=');
	}
	else
	{
		lstnew->variable = ft_strdup(value);
		lstnew->value = NULL; 
	}
	lstnew->next = NULL;
	return (lstnew);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
void	ft_lstadd_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}
void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*newnode;

	newnode = *lst;
	if (newnode == NULL)
	{
		*lst = new;
		return ;
	}
	while (newnode->next != NULL)
		newnode = newnode->next;
	newnode->next = new;
}
