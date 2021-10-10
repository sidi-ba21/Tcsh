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
    char *str = my_strcat("/tmp", "/.alias42");

    stat(str, &sts);
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
    char *str = my_strcat("/tmp", "/.alias42");
    int fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0664);
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

int if_alias_exist(char *str)
{
    char **tmp = NULL;
    char **ptr = NULL;
    size_t ssize = 0;
    char *temp = NULL;
    char *path = my_strcat("/tmp", "/.alias42");
    FILE *alias = fopen(path, "r");

    if (alias == NULL || str == NULL)
        return (0);
    ptr = my_str_to_word_array(str);
    for (int gibline = getline(&temp, &ssize, alias); gibline != -1;
    gibline = getline(&temp, &ssize, alias)) {
        tmp = my_str_to_word_array_delim(temp, ";\n");
        if (my_strcmp(ptr[0], tmp[0]) == 0) {
            fclose(alias);
            return (1);
        }
    }
    fclose(alias);
    return (0);
}

static char *replace_alias(char *str, char *alias)
{
    char **tmp = NULL;
    char **ptr = NULL;
    char *new = NULL;

    if (alias == NULL)
        return (str);
    ptr = my_str_to_word_array(str);
    tmp = my_str_to_word_array_delim(alias, ";\n");
    if (my_strcmp(ptr[0], tmp[0]) == 0) {
        new = my_strcat(tmp[1], &str[my_strlen(tmp[0])]);
        return (new);
    }
    return (str);
}

char *replace_cmd_with_alias(char *str)
{
    size_t ssize = 0;
    char *temp = NULL;
    char *path = my_strcat("/tmp", "/.alias42");
    FILE *alias = fopen(path, "r");

    if (alias == NULL)
        return (0);
    for (int gibline = getline(&temp, &ssize, alias); gibline != -1;
    gibline = getline(&temp, &ssize, alias)) {
        str = replace_alias(str, temp);
    }
    fclose(alias);
    return (str);
}