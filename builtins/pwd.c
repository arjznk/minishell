#include "minishell.h"

void    ft_pwd(char *str)
{
    char buf[BUFFER_SIZE];
    if(ft_strncmp(str, "pwd", 3) == 0)
    {
        getcwd(buf, BUFFER_SIZE);
        if(getcwd(buf, BUFFER_SIZE) ==  NULL)
            perror("Error:");
        printf("%s\n", buf);
    }
}