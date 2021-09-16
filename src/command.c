/*
** EPITECH PROJECT, 2021
** command
** File description:
** command make
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "minishell.h"

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

int my_cd(char *strcmd)
{
    if (chdir(strcmd) == -1) {
        my_errorstr(strcmd);
        if (access(strcmd, F_OK) == 0)
            my_errorstr(": Not a directory.\n");
        else
            my_errorstr(": No such file or directory.\n");
    }
    return 0;
}

int cmdcd(char **strcmd, char **env)
{
    int i = 0;

    reset_env(env);
    for (; strcmd[i]; i++);
    if (i > 2) {
        my_errorstr("cd: Too many arguments.\n");
        return 0;
    }
    if (strcmd[1] == NULL) {
        chdir(my_getenv(env, "HOME"));
        return 0;
    }
    if (my_strcmp(strcmd[1], "-") == 0) {
        chdir(my_getenv(env, "OLDPWD"));
        return 0;
    }
    return my_cd(strcmd[1]);
}

int cmdexit(char **strcmd, char **env)
{
    (void) env;
    if (strcmd[0] && my_strcmp("exit", strcmd[0]) == 0) {
        my_putstr("exit\n");
        exit(0);
    }
    return 0;
}
