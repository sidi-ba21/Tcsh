/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** which
*/

#include "minishell.h"
#include <fcntl.h>

int get_which(char *str, char **path)
{
    char *tmp = NULL;

    for (int i = 0; path[i]; i++) {
        tmp = my_strcat(my_strcat(path[i], "/"), str);
        if (access(tmp, F_OK | X_OK) == 0) {
            printf("%s\n", tmp);
            return (0);
        }
    }
    return (my_errorstr(str), my_errorstr(": Command not found.\n"), 1);
}

int cmdwhich(char **cmd, char **env)
{
    char **path = my_str_to_word_array(secur_path);
    int j = 0;

    (void) env;
    if (cmd[1] == NULL)
        return (my_errorstr("which: Too few arguments.\n"), 1);
    for (int i = 1; cmd[i]; i++)
        j = get_which(cmd[i], path);
    return (j);
}