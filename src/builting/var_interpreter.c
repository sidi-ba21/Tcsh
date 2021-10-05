/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** var_interpreter
*/

#include "my.h"
#include "minishell.h"

int set_loc(char **cmd, char **env)
{
    (void)env;
    for (int i = 1; cmd[i]; i++)
        putenv(cmd[i]);
    return (0);
}

int unset_loc(char **cmd, char **env)
{
    (void)env;
    for (int i = 1; cmd[i]; i++)
        unsetenv(cmd[i]);
    return (0);
}