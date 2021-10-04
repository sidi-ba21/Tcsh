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
#include "struct.h"
#include "my.h"

#ifndef MINISHELL_H_
#define MINISHELL_H_

int main(int ac, char **av, char **env);
int my_sh(char **env);
int check_path(char **tab, char **env);
char *my_getenv(char **env, const char *name);
int simple_exec(char **tab, char **env);
int get_exec(char **tmp, char **tab, int j);
int get_cmd(char **strcmd, char **env);
void my_prompt(char **env);

//env
char **create_env(void);
int reset_env(char **env);

//handle_error
void seg_fault(pid_t pid, int status);
int error_op(int *operator);
int null_cmd(char *buffer);

//operator
int *get_operator(char *buffer);

//pipe
int set_pipe(int *operator);

//redirection
char **set_redirection(int *operator, char **tab, char **tmp);

#endif