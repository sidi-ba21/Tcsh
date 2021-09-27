/*
** EPITECH PROJECT, 2021
** setenv
** File description:
** setenv
*/

#include "minishell.h"

int my_setenv(char **strcmd, char **env)
{
    int i = 0;
    char **setenv = env;

    for (i = 0; env[i] && my_strcmp(env[i], strcmd[1]) != 61; i++);
    if (env[i] == NULL) {
        env = malloc(sizeof(char *) * (i + 2));
        env = setenv;
        env[i + 1] = NULL;
    }
    env[i] = my_strcat(strcmd[1], "=");
    if (strcmd[2] != NULL)
        env[i] = my_strcat(env[i], strcmd[2]);
    return 0;
}

int cmdsetenv(char **strcmd, char **env)
{
    int i = 0;

    for (; strcmd[i]; i++);
    if (i == 1) {
        my_show_word_array(env);
        return 0;
    }
    if (i > 3) {
        my_errorstr("setenv: Too many arguments.\n");
        return 0;
    }
    return my_setenv(strcmd, env);
}