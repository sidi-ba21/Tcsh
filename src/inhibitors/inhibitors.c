/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** inhibitors
*/

#include "my.h"
#include <stdlib.h>
#include <stdbool.h>

char *separator_special_char(char *str, char c)
{
    int j = 0;
    char *tmp = malloc(sizeof(char) * (my_strlen(str) * 3));

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c && str[i] != ' ' && str[i - 1] == c) {
            tmp[j++] = ' ';
            tmp[j++] = '\"';
            tmp[j++] = str[i];
        } else if (str[i] != c && str[i] != ' ' && str[i + 1] == c) {
            tmp[j++] = str[i];
            tmp[j++] = ' ';
            tmp[j++] = '\"';
        } else
            tmp[j++] = str[i];
    }
    tmp[j] = '\0';
    free(str);
    return (tmp);
}

int nbr_backslash(char **str, bool end)
{
    int j = 0;
    if (end = false)
}

char **append_str(char **str)
{
    char **tmp = malloc(sizeof(*str));
    int j = 0;

    for (int i = 0; str[i]; i++, j++) {
        tmp[j] = str[i][0] != '\\'
        ? my_strdup(str[i]) : my_strdup(&str[i][1]);
        if (str[i + 1] && str[i][my_strlen(str[i]) - 1] == '\\' &&
        str[i][my_strlen(str[i]) - 2] != '\\') {
            tmp[j] = my_strcat(tmp[j], str[i + 1][0] != '\\' ? str[i + 1] :
            &str[i + 1][1]);
            i++;
        }
    }
    tmp[j] = NULL;
    return (tmp);
}