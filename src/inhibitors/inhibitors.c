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

int nbr_backslash(char *str)
{
    int count = 0;

    for (int j = 0; str[j] != '\0' && str[j] == '\\'; j++)
        count++;
    return (count);
}

int manage_b_slash1(char *str)
{
    char *tmp = malloc(sizeof(char) * my_strlen(str) + 1);
    int i = 0;
    int b_slash = 0;
    int j, k;

    for (; str[i] == '\\' && str[i] != '\0'; i++)
        tmp[i] == str[i];
    for (; str[i] != '\\' && str[i] != '\0'; i++)
        tmp[i] == str[i];
    if (i == my_strlen(str)) {
        free(tmp);
        return (1);
    }
    b_slash = nbr_backslash(&str[i]);
    for (j = i, k = 0; k < b_slash / 2; j++, k++)
        tmp[j] = '\\';
    i += b_slash;
    for (; str[i] != '\0'; i++, j++)
    tmp[j] = str[i];
    tmp[j] = '\0';
    str = my_strcpy(str, tmp);
    return (0);
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