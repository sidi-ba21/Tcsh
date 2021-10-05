/*
** EPITECH PROJECT, 2021
** execution
** File description:
** execution
*/

#include "minishell.h"

int get_cmd(char **strcmd, char **env)
{
    for (int i = 0; i < 4; i++)
        if (strcmd[0] && my_strcmp(tabcmd[i].cmd1, strcmd[0]) == 0) {
            tabcmd[i].cmd2(strcmd, env);
            return 1;
        }
    return 0;
}

int check_path(char **tab, char **env)
{
    char **path = my_getenv(env, "PATH") != NULL ?
    my_str_to_word_array(my_getenv(env, "PATH")) : NULL;
    char *str = NULL;

    if (tab[0] == NULL || path == NULL)
        return -1;
    for (int i = 0; path[i]; i++) {
        str = my_strcat(my_strcat(path[i], "/"), tab[0]);
        if (access(str, F_OK | X_OK) == 0 ||
        access(my_strcat("/", tab[0]), F_OK | X_OK) == 0) {
            tab[0] = access(str, F_OK | X_OK) == 0 ? str :
            my_strcat("/", tab[0]);
            return 1;
        }
    }
    return 0;
}

int simple_exec(char **tab, char **env)
{
    pid_t pid = fork();
    int stat_loc = 0;

    if (pid == -1)
        perror("fork");
    check_path(tab, env);
    if (pid == 0) {
        if (tab[0] && my_strcmp("exit", tab[0]) == 0)
            exit(0);
        execve(tab[0], tab, env);
        my_errorstr(tab[0]);
        my_errorstr(": Command not found.\n");
        exit(0);
    }
    //seg_fault(pid, stat_loc);
    return 0;
}