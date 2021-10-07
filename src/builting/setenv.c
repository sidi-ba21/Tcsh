/*
** EPITECH PROJECT, 2021
** setenv
** File description:
** builting setenv.c
*/

#include "minishell.h"

int is_alpha(char *str, bool chr_eq);

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
    int error = is_alpha(strcmd[1], true);

    for (; strcmd[i]; i++);
    if (i == 1) {
        my_show_word_array(env);
        return 0;
    }
    if (i > 3) {
        my_errorstr("setenv: Too many arguments.\n");
        return -1;
    }
    if (error == 1)
        return (my_errorstr("set: Variable name must begin "),
        my_errorstr("with a letter.\n"));
    else if (error == 2)
        return (my_errorstr("set: Variable name must contain "),
        my_errorstr("alphanumeric characters.\n"));
    return my_setenv(strcmd, env);
}