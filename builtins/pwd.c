#include "minishell.h"

void    ft_pwd()
{
    char buf[BUFFER_SIZE];

    getcwd(buf, BUFFER_SIZE);
    if(getcwd(buf, BUFFER_SIZE) ==  NULL)
        perror("Error:");
    printf("%s\n", buf);
}