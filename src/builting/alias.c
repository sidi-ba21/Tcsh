/*
** EPITECH PROJECT, 2021
** alias
** File description:
** builting alias
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static int disp_alias(int fd)
{
    struct stat sts;
    char *temp = NULL;
    char **tab = NULL;

    stat(".alias", &sts);
    temp = malloc(sizeof(char) * (sts.st_size + 1));
    read(fd, temp, sts.st_size);
    tab = my_str_to_word_array_delim(temp, ";\n");
    for (int i = 0; tab[i]; i += 2) {
        my_putstr(tab[i]);
        my_putchar('\t');
        my_putstr(tab[i + 1]);
        my_putchar('\n');
    }
    free(temp);
    close(fd);
    return 0;
}

int update_alias(char **strcmd, char **env __attribute__((unused)))
{
    int fd = open(".alias", O_RDWR | O_CREAT | O_APPEND, 0664);
    int size = 0;

    for (; strcmd[size]; ++size);
    if (size == 1)
        return disp_alias(fd);
    if (size < 3)
        return 0;
    write(fd, strcmd[1], my_strlen(strcmd[1]));
    write(fd, ";", 1);
    for (int i = 2; strcmd[i]; i++) {
        write(fd, strcmd[i], my_strlen(strcmd[i]));
        if (i != size - 1)
            write(fd, " ", 1);
    }
    write(fd, "\n", 1);
    return close(fd);
}

static char *replace_alias(char *target, char *replace)
{
    int j = 0;
    int cmt = 0;
    char *res = calloc(my_strlen(target) + my_strlen(replace) + 1,
    sizeof(char));

    for (int i = 0; i < my_strlen(target) + my_strlen(replace); i++) {
        res[i] = target[cmt];
        if (target[cmt] == replace[0]) {
            for (j = 0; replace[j]; j++)
                res[i + j] = replace[j];
            i += j;
        }
        cmt++;
    }
    return res;
}

static char *trim_string(char *str)
{
    int column = 0;
    char *res = calloc(my_strlen(str), sizeof(char));

    for (; str[column] && str[column] != ';'; ++column);
    for (int i = column + 1; str[i]; i++)
        res[i - column - 1] = str[i];
    if (res[my_strlen(res) - 1] == 10)
        res[my_strlen(res) - 1] = 0;
    return res;
}

char *replace_cmd_with_alias(char *str)
{
    size_t ssize;
    char *temp = NULL;
    FILE *alias = fopen(".alias", "r");
    char **tab = my_str_to_word_array_delim(str, " \t");

    if (alias == NULL)
        return str;
    for (int gibline = getline(&temp, &ssize, alias); gibline != -1;
    gibline = getline(&temp, &ssize, alias)) {
        for (int i = 0; tab[i]; i++) {
            if (my_strncmp(temp, tab[i], my_strlen(tab[i])) == 0) {
                str = replace_alias(str, trim_string(temp));
            }
        }
    }
    return str;
}