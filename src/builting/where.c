/*
** EPITECH PROJECT, 2021
** where
** File description:
** where
*/

#include "minishell.h"
#include <fcntl.h>

int is_built(char *str);

int get_alias(char *str, bool wh);

int get_where(char *str, char **path)
{
    char *tmp = NULL;
    int j = 0;

    is_built(str) == 0 ? printf("%s is a shell built-in\n", str) : 0;
    for (int i = 0; path[i]; i++) {
        tmp = my_strcat(my_strcat(path[i], "/"), str);
        if (access(tmp, F_OK | X_OK) == 0) {
            printf("%s\n", tmp);
            j = 0;
        }
        else
            j = 1;
    }
    return (j);
}

int cmdwhere(char **cmd, char **env)
{
    char **path = my_str_to_word_array(secur_path);
    int j = 0;

    (void) env;
    if (cmd[1] == NULL)
        return (my_errorstr("where: Too few arguments.\n"), 1);
    for (int i = 1; cmd[i]; i++) {
        get_alias(cmd[i], false);
        j = get_where(cmd[i], path);
    }
    return (j);
}