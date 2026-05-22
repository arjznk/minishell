#include "minishell.h"

void    ft_cd(char *str)
{
    DIR *dir;

    dir = opendir(str);
    closedir(dir);
}