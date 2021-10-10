/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** system_exec
*/

#include "minishell.h"
#include "my.h"

char **status_set(int stat_loc);

int nbr_of_chr(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            count++;
    return (count);
}

int sys_exec(char *str)
{
    if (nbr_of_chr(str, '`') % 2 == 1) {
        fprintf(stderr, "Unmatched '`'.\n");
        return (-1);
    }
    if (nbr_of_chr(str, '(') != nbr_of_chr(str, ')')) {
        fprintf(stderr, "Too many ('s.\n");
        return (-1);
    }
    if (nbr_of_chr(str, '\'') % 2 == 1) {
        fprintf(stderr, "Unmatched '\''.\n");
        return (-1);
    }
    if (nbr_of_chr(str, '"') % 2 == 1) {
        fprintf(stderr, "Unmatched '\"'.\n");
        return (-1);
    }
    set_loc(status_set(WEXITSTATUS(system(str))), NULL);
    return (0);
}