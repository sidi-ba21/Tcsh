/*
** EPITECH PROJECT, 2021
** segfault
** File description:
** seg
*/

#include "minishell.h"

int my_echo(char **strcmd, char **env)
{
    (void) env;
    for (int x = 1; strcmd[x]; x++) {
        my_printf("%s", strcmd[x]);
        if (strcmd[x])
            my_putstr(" ");
    }
    my_putstr("\n");
    return 0;
}