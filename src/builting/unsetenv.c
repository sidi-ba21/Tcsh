/*
** EPITECH PROJECT, 2021
** unsetenv
** File description:
** unsetenv builting
*/

#include "minishell.h"

int cmdunsetenv(char **strcmd, char **env)
{
    int i = 0;
    int j = 0;
    int count = 0;

    if (strcmd[1] == NULL) {
        my_errorstr("unsetenv: Too few arguments.\n");
        return 0;
    }
    for (; env[i]; i++) {
        for (count = 0; strcmd[count] &&
        my_strcmp(env[i], strcmd[count]) != 61; count++);
        if (strcmd[count] != NULL)
            j++;
        else
            env[i - j] = my_strdup(env[i]);
    }
    env[i - j] = NULL;
    return 0;
}