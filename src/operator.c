/*
** EPITECH PROJECT, 2021
** operator
** File description:
** operator
*/

#include "minishell.h"

int simple_exec(char **tab, char **env)
{
    pid_t pid = fork();

    if (pid == -1)
        perror("fork");
    check_path(tab, env);
    if (pid == 0) {
        if (tab[0] && my_strcmp("exit", tab[0]) == 0)
            exit(0);
        execve(tab[0], tab, env);
        my_errorstr(tab[0]);
        my_errorstr(": Command not found.\n");
        exit(0);
    }
    return 0;
}

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

int set_pipe(int *operator)
{
    static unsigned short i = 0;
    static int pfd[2][2];

    if (operator[IN] == PIPE) {
        dup2(pfd[i][IN], STDIN_FILENO);
        close(pfd[i][IN]);
        i = operator[OUT] != 2 ? 0 : i == 1 ? 0 : 1;
    }
    if (operator[OUT] == PIPE) {
        pipe(pfd[i]);
        dup2(pfd[i][OUT], STDOUT_FILENO);
        close(pfd[i][OUT]);
    }
    return 0;
}

char **set_redirection(int *operator, char **tab, char **tmp)
{
    int fd;

    if (operator[IN] == 3)
        fd = open(tab[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (operator[IN] == 4 || operator[IN] == 6 || operator[IN] == 5)
        fd = open(tab[0], O_RDWR | O_CREAT | O_APPEND, 0664);
    if (operator[IN] == 3 || operator[IN] == 4)
        dup2(fd, STDOUT_FILENO);
    if (operator[IN] == 5 || operator[IN] == 6)
        dup2(fd, STDIN_FILENO);
    if (operator[IN] > 2) {
        close(fd);
        return tmp;
    }
    return tab;
}