#include "minishell.h"

void    set_sig_childen(void)
{
    struct sigaction sa;

    bzero(&sa, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
}

void    set_sig_parent(void)
{
    struct sigaction sa;

    bzero(&sa,sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);

}

/*
si signal : exec->status = 130;

*/