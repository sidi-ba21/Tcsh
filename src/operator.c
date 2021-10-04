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

int count_op(char *buffer)
{
    int op = 0;

    for (int i = 0; buffer[i]; i++)
        if (buffer[i] == ';' || buffer[i] == '|' ||
        buffer[i] == '>' || buffer[i] == '<')
            op++;
    return op + 2;
}

int *get_operator(char *buffer)
{
    int *operator = malloc(sizeof(int) * count_op(buffer));
    int j = 0;

    operator[j++] = 1;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == ';')
            operator[j++] = SEMICOLON;
        if (buffer[i] == '|')
            operator[j++] = PIPE;
        if (buffer[i] == '>' && buffer[i + 1] != '>')
            operator[j++] = REDIRECTION_OUT1;
        if (buffer[i] == '>' && buffer[++i] == '>')
            operator[j++] = REDIRECTION_OUT2;
        if (buffer[i] == '<' && buffer[i + 1] != '<')
            operator[j++] = REDIRECTION_IN1;
        if (buffer[i] == '<' && buffer[++i] == '<')
            operator[j++] = REDIRECTION_IN2;
    }
    operator[j] = 0;
    return operator;
}