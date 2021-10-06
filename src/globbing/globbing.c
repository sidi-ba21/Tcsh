/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** globbing
*/

#include "minishell.h"
#include "my.h"
#include <wordexp.h>

static bool is_chr_in_str(char const *s)
{
    if (s == NULL)
        return false;
    for (int i = 0; s[i]; i++)
        if (s[i] == '*' || s[i] == '[' || s[i] == '?' || s[i] == '{')
            return true;
    return false;
}

static size_t tab_len(char **tab)
{
    size_t size = 0;

    for (; tab && tab[size]; size++);
    return size;
}

static char **cat_glob_to_array(char **tab, wordexp_t exp)
{
    size_t i = 0;
    size_t len = tab_len(tab);
    char **tmp = malloc(sizeof(char *) * (len + exp.we_wordc + 1));

    if (!tmp) {
        dprintf(2, "Malloc failed.\n");
        exit(84);
    }
    for (; i != len; i++) {
        tmp[i] = strdup(tab[i]);
        if (!tmp[i]) {
            dprintf(2, "Malloc failed.\n");
            exit(84);
        }
    }
    for (size_t j = 0; j < exp.we_wordc; j++)
        tmp[i + j] = strdup(exp.we_wordv[j]);
    tmp[len + exp.we_wordc] = NULL;
    return tmp;
}

static char **cat_simple_array(char **tab, char *to_add)
{
    size_t len = tab_len(tab);
    char **tmp = malloc(sizeof(char *) * (len + 2));

    if (!tmp) {
        dprintf(2, "Malloc failed.\n");
        exit(84);
    }
    for (size_t i = 0; i != len; i++) {
        tmp[i] = strdup(tab[i]);
        if (!tmp[i]) {
            dprintf(2, "Malloc failed.\n");
            exit(84);
        }
    }
    tmp[len] = to_add;
    tmp[len + 1] = NULL;
    return tmp;
}

char **globbing(char **av)
{
    char **tab = NULL;
    wordexp_t exp = {0};

    if (!*av)
        return av;
    for (int i = 0; av[i] != NULL; i++) {
        if (!is_chr_in_str(av[i])) {
            tab = cat_simple_array(tab, av[i]);
            continue;
        }
        wordexp(av[i], &exp, WRDE_NOCMD);
        tab = cat_glob_to_array(tab, exp);
        wordfree(&exp);
    }
    return tab;
}