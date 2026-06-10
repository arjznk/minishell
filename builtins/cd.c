#include "minishell.h"

void    ft_cd(char *str, t_path *path)
{
    // DIR *dir;
    (void)str;
    // dir = opendir(ft_strchr(str, 'd'));
    chdir(path->access_usr);
    // closedir(dir);
}