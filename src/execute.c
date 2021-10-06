/*
** EPITECH PROJECT, 2021
** execution
** File description:
** execution
*/

#include "minishell.h"
#include "unistd.h"
#include <sys/types.h>
#include <dirent.h>

int get_cmd(char **strcmd, char **env)
{
    for (int i = 0; i < 7; i++)
        if (strcmd[0] && my_strcmp(tabcmd[i].cmd1, strcmd[0]) == 0) {
            tabcmd[i].cmd2(strcmd, env);
            return 0;
        }
    if (strcmd[0] != NULL)
        simple_exec(strcmd, env);
    return 1;
}

static bool specified_path(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            return (true);
    return (false);
}

int check_path(char **tab, char **env)
{
    char **path = my_getenv(env, "PATH") != NULL ?
    my_str_to_word_array(my_getenv(env, "PATH")) : NULL;
    char *str = NULL;

    if (tab[0] == NULL || path == NULL)
        return -1;
    if (specified_path(tab[0]))
        return (0);
    for (int i = 0; path[i]; i++) {
        str = my_strcat(my_strcat(path[i], "/"), tab[0]);
        if (access(str, F_OK | X_OK) == 0) {
            tab[0] = str;
            return 1;
        }
    }
    return 0;
}

int simple_exec(char **tab, char **env)
{
    pid_t pid = fork();

    if (pid == -1)
        perror("fork");
    check_path(tab, env);
    if (pid == 0) {
        if (tab[0] && my_strcmp("exit", tab[0]) == 0)
            exit(0);
        execve(tab[0], tab, env);
        my_errorstr(tab[0]);
        if ((tab[0][0] == '/' || tab[0][my_strlen(tab[0]) - 1] == '/')
        && opendir(tab[0]) != NULL)
            my_errorstr(": Permission denied.\n");
        else
            my_errorstr(": Command not found.\n");
        exit(1);
    }
    return 0;
}