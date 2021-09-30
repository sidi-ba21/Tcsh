/*
** EPITECH PROJECT, 2021
** framebuffer.h
** File description:
** framebuffer
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"

#ifndef MINISHELL_H_
#define MINISHELL_H_

typedef enum operator_s {
    END = 0,
    SEMICOLON,
    PIPE,
    REDIRECTION_OUT1,
    REDIRECTION_OUT2,
    REDIRECTION_IN1,
    REDIRECTION_IN2,
}operator_t;

typedef enum port_s {
    IN = 0,
    OUT,
    ERR,
}port_t;

typedef struct comand
{
    char *cmd1;
    int (*cmd2)(char **, char **);
}cmd;

typedef struct linked_list_t
{
    char const *data;
    struct linked_list_t *next;
}l_list;

int main(int ac, char **av, char **env);
int error(char **env);
int my_sh(char **env);
int check_path(char **tab, char **env);
int cmdcd(char **strcmd, char **env);
int cmdexit(char **strcmd, char **env);
int cmdenv(char **strcmd, char **env);
int cmdsetenv(char **strcmd, char **env);
int cmdunsetenv(char **strcmd, char **env);
void seg_fault(pid_t pid, int status);
char *my_getenv(char **env, const char *name);
int my_setenv(char **strcmd, char **env);
int sep_pipe(char **str, char **env);
int simple_exec(char **tab, char **env);
int get_exec(char **tmp, char **tab, int j);
int *get_operator(char *buffer);
int set_pipe(int *operator);
char **set_redirection(int *operator, char **tab, char **tmp);
int error_op(int *operator);
int null_cmd(char *buffer);
int get_cmd(char **strcmd, char **env);
void my_prompt(char **env);

static const cmd tabcmd[4] =
{
    {"cd", &cmdcd},
    {"env", &cmdenv},
    {"setenv", &cmdsetenv},
    {"unsetenv", &cmdunsetenv},
};

#endif