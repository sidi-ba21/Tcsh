/*
** EPITECH PROJECT, 2021
** operator
** File description:
** operator
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "minishell.h"

int get_op(char *buffer)
{
    for (int i = 0; i < 8; i++)
        if (my_strcmp(tabop[i].sep, buffer) == 0)
            return tabop[i].op;
    return 0;
}

int count_op(char *buffer)
{
    int op = 2;
    char tmp[3];

    for (int j = 0; buffer[j]; ++j) {
        tmp[0] = buffer[j];
        tmp[1] = buffer[j + 1];
        tmp[0] != tmp[1] ? (tmp[1] = '\0') : (tmp[2] = '\0');
        get_op(tmp) != 0 ? ++j & ++op : 0;
    }
    return op;
}

int *get_operator(char *buffer)
{
    int *operator = malloc(sizeof(int) * count_op(buffer));
    char tmp[3];
    int i = 0;

    operator[i++] = 1;
    for (int j = 0; buffer[j]; j++) {
        tmp[0] = buffer[j];
        tmp[1] = buffer[j + 1];
        tmp[0] != tmp[1] ? (tmp[1] = '\0') : (tmp[2] = '\0');
        if (get_op(tmp) != 0) {
            operator[i++] = get_op(tmp);
            j++;
        }
    }
    operator[i] = 0;
    return operator;
}