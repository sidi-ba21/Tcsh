/*
** EPITECH PROJECT, 2021
** minishell
** File description:
** copy env
*/

#include "minishell.h"

char **copy_env(list_t *list)
{
    int n = 0;
    list_t *tmp = list;
    char **tab = NULL;

    do {
        list = list->next;
        n = n + 1;
    } while (list != tmp);
    tab = malloc(sizeof(char *) * (n + 1));
    for (int i = 0; i < n; i++) {
        tab[i] = my_strdup(tmp->data);
        tmp = tmp->next;
    }
    tab[n] = 0;
    return (tab);
}

void create_env(char **tmp)
{
    size_t size = 0;
    char *buf = NULL;

    tmp[0] = my_strdup("PWD=");
    tmp[0] = my_strcat(tmp[0], getcwd(buf, size));
    tmp[1] = my_strdup("HOST=localhost.localdomain");
    tmp[2] = my_strdup("PATH=/usr/bin:/bin");
    tmp[3] = 0;
    free(buf);
}