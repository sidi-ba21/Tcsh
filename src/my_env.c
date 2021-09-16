/*
** EPITECH PROJECT, 2021
** env
** File description:
** setenv unsetenv env
*/

#include <signal.h>
#include <unistd.h>
#include "minishell.h"

int cmdenv(char **strcmd __attribute__((unused)), char **env)
{
    return my_show_word_array(env);
}

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

char *my_getenv(char **env, const char *name)
{
    int i = 0;
    int namelen = my_strlen(name);

    for (; env[i] && my_strncmp(env[i], name, namelen) != 0; i++);

    if (env[i] == NULL)
        return NULL;
    return &env[i][namelen + 1];
}