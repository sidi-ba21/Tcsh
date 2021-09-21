/*
** EPITECH PROJECT, 2021
** env.c
** File description:
** setenv and unsetenv
*/

#include "minishell.h"

list_t *my_setenv(list_t *list, char **str)
{
    list_t *tmp = list;

    str[0] = my_strcat(str[0], "=");
    do {
        if (my_strncmp(list->data, str[0], my_strlen(str[0])) == 0) {
            list->data = my_strdup(str[0]);
            if (str[1] != NULL)
                list->data = my_strcat(list->data, str[1]);
            return (list);
        }
        list = list->next;
    } while (list != tmp);
    if (str[1] != NULL)
        str[0] = my_strcat(str[0], str[1]);
    list = add_to_list(list, str[0]);
    return (list);
}

int cmdsetenv(list_t *list, char **str)
{
    if (my_tab_length(str) > 3)
        return (my_put_error("setenv: Too many arguments.\n"));
    else if (str[1] != NULL) {
        if (list == NULL)
            list = push(&list, str[1]);
        list = my_setenv(list, &str[1]);
    }
    else
        printlist(list);
    return (0);
}

int cmdunsetenv(list_t *list, char **str)
{
    if (str[1] == NULL)
        return (my_put_error("unsetenv: Too few arguments.\n"));
    else {
        for (int i = 1; str[i]; i++)
            del_node(&list, str[i]);
    }
    return (0);
}

int cmdenv(list_t *list, char **str)
{
    if (my_tab_length(str) > 1)
        my_printf("%s: ‘%s’: No such file or directory\n", str[0], str[1]);
    else
        printlist(list);
    return (0);
}

char *my_getenv(list_t *list, char *s)
{
    char *str = NULL;
    int j = 0;
    list_t *tmp = list;

    if (tmp == NULL)
        return (NULL);
    do {
        if (my_strncmp(list->data, s, my_strlen(s)) == 0) {
            for (j = 0; list->data[j] != '='; j++);
            j++;
            str = my_strdup(&list->data[j]);
            return (str);
        }
        list = list->next;
    } while (list != tmp);
    return (NULL);
}