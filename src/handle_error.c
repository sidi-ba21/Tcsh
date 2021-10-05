/*
** EPITECH PROJECT, 2021
** segfault
** File description:
** seg
*/

#include <signal.h>
#include <string.h>
#include "minishell.h"

void seg_fault(int stat_loc)
{
    wait(&stat_loc);
    if (WIFSIGNALED(stat_loc)) {
        if (WTERMSIG(stat_loc) == SIGSEGV && WCOREDUMP(stat_loc))
            my_errorstr("Segmentation fault (core dumped)\n");
        else if (WTERMSIG(stat_loc) == SIGSEGV)
            my_errorstr("Segmentation fault\n");
        if (WTERMSIG(stat_loc) == SIGFPE && WCOREDUMP(stat_loc))
            my_errorstr("Floating exception (core dumped)\n");
        else if (WTERMSIG(stat_loc) == SIGFPE)
            my_errorstr("Floating exception\n");
    }
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
    int count = 0;
    int null_cmd = 0;
    char *tmp = my_strdup(buffer);

    for (int i = 0; buffer[i]; i++) {
        if (my_alphanum(buffer[i]) == 1)
            count++;
        if (buffer[i] == '|' || (buffer[i] == '<' && buffer[i + 1] != '<') ||
        (buffer[i] == '>' && buffer[i + 1] != '>') || buffer[i] == '\n')
            count == 0 ? null_cmd++ : (count = 0);
    }
    if (strtok(tmp, "; \t\n") != NULL && null_cmd > 0) {
        my_errorstr("Invalid null command.\n");
        return -1;
    }
    return 0;
}