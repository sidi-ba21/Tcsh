/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** parsing input
*/

#include "minishell.h"

int check_input2(char *str)
{
    for (int j = 0; str[j] != '\0'; j++) {
        if (j > 0 && str[j] == '|' && str[j - 1] == '>') {
            my_put_error("Ambiguous output redirect.\n");
            free(str);
            return (-1);
        }
        if (str[j] == '|' && str[j + 1] == '<') {
            my_put_error("Ambiguous input redirect.\n");
            free(str);
            return (-1);
        }
    }
    free(str);
    return (0);
}

int check_input3(char **tab)
{
    int j = 0;
    int i = 0;

    for (int k = 0; tab[k]; k++) {
        if ((my_strncmp(tab[k], ">", 1) == 0 ||
        my_strncmp(tab[k], "<", 1) == 0) && tab[k + 1] == NULL) {
            my_put_error("Missing name for redirect.\n");
            return (-1);
        }
        i = my_strncmp(tab[k], ">", 1) == 0 ? i + 1 : i;
        j = my_strncmp(tab[k], "<", 1) == 0 ? j + 1 : j;
        if (i > 1 || j > 1) {
            i > 1 ? my_put_error("Ambiguous output redirect.\n") :
                my_put_error("Ambiguous input redirect.\n");
            return (-1);
        }
    }
    return (0);
}

char *command_op(char **tab)
{
    char *tmp = malloc(sizeof(char) * my_tab_length(tab));
    int j = 0;

    for (int i = 0; tab[i]; i++) {
        if (my_strncmp(tab[i], "|", 1) == 0 ||
            my_strncmp(tab[i], ">", 1) == 0
            || my_strncmp(tab[i], "<", 1) == 0)
            tmp[j++] = tab[i][0];
    }
    tmp[j++] = '\0';
    return (tmp);
}

int check_input(char **tab)
{
    char *tmp = command_op(tab);

    for (int i = 0; tab[i]; i++) {
        if (my_strcmp(tab[i], "|") == 0 &&
        ((i > 0 && my_str_isalphanum(tab[i - 1]) == 0) ||
        (tab[i + 1] && my_str_isalphanum(tab[i + 1]) == 0))) {
            my_put_error("Missing name for redirect.\n");
            return (-1);
        }
        if (my_strcmp(tab[i], "|") == 0 &&
        (tab[i + 1] == NULL || my_strcmp(tab[i + 1], "|") == 0 || i == 0)) {
            my_put_error("Invalid null command.\n");
            return (-1);
        }
    }
    if (check_input2(tmp) == -1)
        return (-1);
    if (check_input3(tab) == -1)
        return (-1);
    return (0);
}