/*
** EPITECH PROJECT, 2021
** repeat
** File description:
** repeat
*/

#include "minishell.h"

int cmdrepeat(char **strcmd, char **env)
{
    if (strcmd[1] == NULL || strcmd[2] == NULL) {
        dprintf(2, "%s: Too few arguments.\n", strcmd[0]);
        return -1;
    }
    if (my_str_isnum(strcmd[1]) == 0) {
        dprintf(2, "%s: Badly formed number.\n", strcmd[0]);
        return -1;
    }
    for (int i = 0; i < atoi(strcmd[1]); i++)
        simple_exec(&strcmd[2], env);
    return 0;
}