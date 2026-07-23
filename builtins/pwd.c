#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[BUFFER_SIZE];

	if (getcwd(buf, BUFFER_SIZE) == NULL)
		printf("minishell: pwd: %s\n", strerror(errno));
	printf("%s\n", buf);
}
