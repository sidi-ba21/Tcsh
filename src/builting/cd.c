/*
** EPITECH PROJECT, 2021
** cd
** File description:
** builting cd
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "minishell.h"

int error_cd(char **strcmd)
{
    int i = 0;

    for (; strcmd[i]; i++);
    if (i > 2) {
        my_errorstr("cd: Too many arguments.\n");
        return -1;
    }
    return (0);
}

int cmdcd(char **strcmd, char **env)
{
    if (error_cd(strcmd) == -1)
        return (-1);
    if (strcmd[1] == NULL) {
        if (chdir(my_getenv(env, "HOME")) == -1)
            my_errorstr("cd: No home directory.\n");
    }
    else if (my_strcmp(strcmd[1], "-") == 0) {
        if (chdir(my_getenv(env, "OLDPWD")) == -1)
            my_errorstr(": No such file or directory.\n");
    }
    else {
        if (chdir(strcmd[1]) == -1) {
            dprintf(2, "%s: %s.\n", strcmd[1], strerror(errno));
            return -1;
        }
    }
    return reset_env(env);
}