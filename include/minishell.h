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
#include <stdbool.h>
#include <string.h>
#include "struct.h"
#include "my.h"
#include <errno.h>

#ifndef MINISHELL_H_
#define MINISHELL_H_

#define secur_path  "/usr/local/bin:/usr/bin"

int my_sh(char **env);
int check_path(char **tab, char **env);
char *my_getenv(char **env, const char *name);
int simple_exec(char **tab, char **env);
int get_exec(char **tmp, char **tab, int j);
int get_cmd(char **strcmd, char **env);
void my_prompt(char **env);
int logical_operator(int operator, int count, bool *stop);
int semicolon_end(int operator, bool *stop);

//env
char **create_env(void);
int reset_env(char **env);

//handle_error
pid_t seg_fault(int *stat_loc);
int error_op(int *operator);
int null_cmd(char *buffer);

//operator
int *get_operator(char *buffer);

//pipe
int set_pipe(int *operator);

//redirection
int set_redirection(int *operator, char ***tab, char ***tmp);

//history
void update_history(char *cmd);

//globbing
char **globbing(char **av);

int sys_exec(char *str);
int nbr_of_chr(char *str, char c);

#endif