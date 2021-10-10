/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** which
*/

#include "minishell.h"
#include <fcntl.h>

int get_alias(char *str, bool wh)
{
    char **tmp = NULL;
    size_t ssize = 0;
    char *temp = NULL;
    char *path = my_strcat("/tmp", "/.alias42");
    FILE *alias = fopen(path, "r");

    if (alias == NULL || str == NULL)
        return (0);
    for (int gibline = getline(&temp, &ssize, alias); gibline != -1;
    gibline = getline(&temp, &ssize, alias)) {
        tmp = my_str_to_word_array_delim(temp, ";\n");
        if (my_strcmp(str, tmp[0]) == 0) {
            wh == true ? my_printf("%s:\t aliased to %s\n", str, tmp[1]) :
            my_printf("%s is aliased to %s", str, tmp[1]);
            fclose(alias);
            return (1);
        }
    }
    fclose(alias);
    return (0);
}

int is_built(char *str)
{
    for (int i = 0; tabcmd[i].cmd1 != NULL; i++) {
        if (str && my_strcmp(tabcmd[i].cmd1, str) == 0)
            return (0);
    }
    return (1);
}

int get_which(char *str, char **path)
{
    char *tmp = NULL;

    if (is_built(str) == 0)
        return printf("%s: shell built-in command.\n", str);
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
    for (int i = 1; cmd[i]; i++) {
        if (get_alias(cmd[i], true) != 1)
            j = get_which(cmd[i], path);
    }
    return (j);
}