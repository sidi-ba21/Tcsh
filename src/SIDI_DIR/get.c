/*
** EPITECH PROJECT, 2021
** get.c
** File description:
** get.c
*/

#include "minishell.h"
#include <sys/wait.h>

void my_prompt(list_t *list);

int is_builtin(char *str)
{
    if (my_strcmp(str, "cd") == 0 || my_strcmp(str, "env") == 0
        || my_strcmp(str, "setenv") == 0 || my_strcmp(str, "unsetenv") == 0
        || my_strcmp(str, "exit") == 0)
        return (1);
    return (0);
}

char *get_path(char *str, list_t *list)
{
    char *s = my_getenv(list, "PATH");
    char **tab = my_str_to_word_array_delim(s, ":");

    free(s);
    if (str == NULL)
        return NULL;
    if (is_builtin(str) == 1) {
        free_double_tab(tab);
        return (str);
    }
    for (int i = 0; tab[i]; i++) {
        if (access(my_strcat(my_strcat(tab[i], "/"), str), F_OK | X_OK) == 0) {
            str = my_strcat(my_strcat(tab[i], "/"), str);
            free_double_tab(tab);
            return (str);
        }
    }
    free_double_tab(tab);
    return (str);
}

void my_prompt(list_t *list)
{
    char *str = my_getenv(list, "PWD");
    int k = 0;

    if (my_getenv(list, "USER") == NULL || str == NULL) {
        my_printf("\033[1;32m[mysh@localhost ~]$\033[1;37m ");
        return;
    }
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            k = i;
    k++;
    my_printf("\033[1;32m[%s@localhost %s]$\033[1;37m ",
    my_getenv(list, "USER"), k > 1 ? &str[k] : "~");
}

char **my_getline(char **tp, list_t *list)
{
    size_t n = 0;
    char *tmp = NULL;
    char *input = NULL;

    isatty(0) == 1 ? my_prompt(list) : 0;
    if (getline(&tmp, &n, stdin) == -1) {
        isatty(0) == 1 ? my_putstr("exit\n") : 0;
        free(list);
        exit(0);
    }
    input = clean_input(tmp);
    tp = my_str_to_word_array_delim(input, ";");
    free(input);
    return (tp);
}

int my_exec(char **tab, list_t *list)
{
    char **tmp = NULL;

    if (tab[0] == NULL)
        return (0);
    for (int i = 0; tab[i]; i++) {
        tmp = my_str_to_word_array(tab[i], ' ');
            operator(tmp, list, true);
        free_double_tab(tmp);
    }
    return (0);
}