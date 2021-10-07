/*
** EPITECH PROJECT, 2021
** segfault
** File description:
** seg
*/

#include <signal.h>
#include <string.h>
#include "minishell.h"

char **status_set(int stat_loc)
{
    char **str = malloc(sizeof(char *) * 3);

    str[0] = my_strdup("set");
    str[1] = my_strdup(my_strcat("status=", my_nbrtostr(stat_loc)));
    str[2] = NULL;
    return (str);
}

pid_t seg_fault(int *stat_loc)
{
    pid_t pid = wait(stat_loc);
    char **tab = status_set(WEXITSTATUS(*stat_loc));

    set_loc(tab, NULL);
    if (WTERMSIG(*stat_loc) == SIGSEGV && WCOREDUMP(*stat_loc))
        my_errorstr("Segmentation fault (core dumped)\n");
    else if (WTERMSIG(*stat_loc) == SIGSEGV)
        my_errorstr("Segmentation fault\n");
    if (WTERMSIG(*stat_loc) == SIGFPE && WCOREDUMP(*stat_loc))
        my_errorstr("Floating exception (core dumped)\n");
    else if (WTERMSIG(*stat_loc) == SIGFPE)
        my_errorstr("Floating exception\n");
    return pid;
}

int error_op(int *operator)
{
    for (int i = 0; operator[i] != 0; i++) {
        if (operator[i] == PIPE && (operator[i + 1] == REDIRECTION_IN1 ||
        operator[i + 1] == REDIRECTION_IN2)) {
            my_errorstr("Ambiguous input redirect.\n");
            return -1;
        }
        if (operator[i + 1] == PIPE && (operator[i] == REDIRECTION_OUT1 ||
        operator[i] == REDIRECTION_OUT2)) {
            my_errorstr("Ambiguous output redirect.\n");
            return -1;
        }
    }
    return 0;
}

int null_cmd(char *buffer)
{
    (void) buffer;
    int null_cmd = 0;

    return null_cmd;
}