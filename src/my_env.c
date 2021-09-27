/*
** EPITECH PROJECT, 2021
** env
** File description:
** setenv unsetenv env
*/

#include "minishell.h"

int cmdenv(char **strcmd __attribute__((unused)), char **env)
{
    return my_show_word_array(env);
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