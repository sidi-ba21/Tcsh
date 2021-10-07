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

int my_cd(char *strcmd)
{
    if (chdir(strcmd) == -1) {
        my_errorstr(strcmd);
        if (access(strcmd, F_OK) == 0)
            my_errorstr(": Not a directory.\n");
        else
            my_errorstr(": No such file or directory.\n");
        return -1;
    }
    return 0;
}

int cmdcd(char **strcmd, char **env)
{
    int i = 0;

    for (; strcmd[i]; i++);
    if (i > 2) {
        my_errorstr("cd: Too many arguments.\n");
        return -1;
    }
    if (strcmd[1] == NULL) {
        if (chdir(my_getenv(env, "HOME")) == -1)
            my_errorstr("cd: No home directory.\n");
    }
    else if (my_strcmp(strcmd[1], "-") == 0) {
        if (chdir(my_getenv(env, "OLDPWD")) == -1)
            my_errorstr(": No such file or directory.\n");
    }
    else
        return my_cd(strcmd[1]);
    reset_env(env);
    return 0;
}