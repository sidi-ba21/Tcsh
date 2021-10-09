/*
** EPITECH PROJECT, 2021
** signal
** File description:
** signal_handler
*/

#include "minishell.h"
#include <signal.h>

void handle_sigint(int sig)
{
    char *str = getcwd(NULL, 0);
    char *user = getenv("USER");
    int k = 0;

    signal(sig, SIG_IGN);
    printf("\n");
    if (str == NULL || user == NULL) {
        isatty(0) == 1 ?
        my_putstr("\033[1;32m[mysh@localhost ~]$\033[1;37m ") : 0;
        return;
    }
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            k = i;
    k++;
    isatty(0) == 1 ? my_printf("\033[1;32m[%s@localhost %s]$\033[1;37m ",
    user, k > 1 ? &str[k] : "~") : 0;
}

void signal_handle(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, SIG_IGN);
}