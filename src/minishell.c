/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** minishell1 -> cd, setenv, unsetenv, env, exit
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

int get_cmd(char **strcmd, char **env)
{
    for (int i = 0; i < 4; i++)
        if (strcmd[0] && my_strcmp(tabcmd[i].cmd1, strcmd[0]) == 0) {
            tabcmd[i].cmd2(strcmd, env);
            return 1;
        }
    return 0;
}

int check_path(char **tab, char **env)
{
    char **path = my_str_to_word_array(my_getenv(env, "PATH"));
    char *str = NULL;

    if (tab[0] == NULL)
        return -1;
    for (int i = 0; path[i]; i++) {
        str = my_strcat(my_strcat(path[i], "/"), tab[0]);
        if (access(str, F_OK | X_OK) == 0) {
            tab[0] = str;
            return 1;
        }
    }
    return 0;
}

int set_cmd(char **tab, int *operator, char **env, int *save_std)
{
    static char **tmp;
    static int k = 0;

    set_pipe(operator);
    tab = set_redirection(operator, tab, tmp);
    if (operator[OUT] > 2) {
        tmp = tab;
        return 0;
    }
    if (tab[0] && get_cmd(tab, env) != 1) {
        simple_exec(tab, env);
        k++;
    }
    if (operator[OUT] == SEMICOLON || operator[OUT] == END)
        for (; k > 0; k--)
            wait(NULL);
    operator[OUT] == SEMICOLON || operator[OUT] == END ? cmdexit(tab, env) : 0;
    dup2(save_std[IN], STDIN_FILENO);
    dup2(save_std[OUT], STDOUT_FILENO);
    return 0;
}

int exec_cmd(char *buffer, char **env)
{
    char **tab = NULL;
    int *operator = get_operator(buffer);
    int save_std[2];

    save_std[IN] = dup(STDIN_FILENO);
    save_std[OUT] = dup(STDOUT_FILENO);
    if (null_cmd(buffer) == -1 || error_op(operator) == -1)
        return -1;
    buffer = strtok(buffer, ";|><\n");
    for (int i = 0; buffer != NULL; i++) {
        tab = my_str_to_word_array(buffer);
        set_cmd(tab, &operator[i], env, save_std);
        buffer = strtok(NULL, ";|><\n");
    }
    return 0;
}

int my_sh(char **env)
{
    size_t bufsize = 0;
    char *buffer = NULL;

    my_prompt(env);
    while (getline(&buffer, &bufsize, stdin) != -1) {
        exec_cmd(buffer, env);
        my_prompt(env);
    }
    return 0;
}