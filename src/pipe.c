/*
** EPITECH PROJECT, 2021
** pipe
** File description:
** pipe
*/

#include "minishell.h"

int set_pipe(int *operator)
{
    static unsigned short i = 0;
    static int pfd[2][2];

    if (operator[IN] == PIPE) {
        dup2(pfd[i][IN], STDIN_FILENO);
        close(pfd[i][IN]);
        i = operator[OUT] != 2 ? 0 : i == 1 ? 0 : 1;
    }
    if (operator[OUT] == PIPE) {
        pipe(pfd[i]);
        dup2(pfd[i][OUT], STDOUT_FILENO);
        close(pfd[i][OUT]);
    }
    return 0;
}