/*
** EPITECH PROJECT, 2021
** env
** File description:
** setenv unsetenv env
*/

#include <signal.h>
#include <unistd.h>
#include "minishell.h"

char **create_env(void)
{
    char **base_env = malloc(sizeof(char *) * 4);

    base_env[0] = my_strdup("PWD=");
    base_env[0] = my_strcat(base_env[0], getcwd(NULL, 0));
    base_env[1] = my_strdup("HOST=localhost.localdomain");
    base_env[2] = my_strdup("PATH=/usr/bin:/bin");
    base_env[3] = 0;
    return (base_env);
}

int reset_env(char **env)
{
    char *pwd = getcwd(NULL, 0);
    char *oldpwd = my_getenv(env, "PWD");

    if (my_strcmp(pwd, oldpwd) != 0) {
        my_setenv((char *[]) {"/setenv", "OLDPWD", oldpwd}, env);
        my_setenv((char *[]) {"/setenv", "PWD", pwd}, env);
    }
    return (0);
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