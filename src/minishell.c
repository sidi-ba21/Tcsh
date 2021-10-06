/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** minishell1 -> cd, setenv, unsetenv, env, exit
*/

#include <unistd.h>
#include <string.h>
#include "minishell.h"

void my_prompt(char **env)
{
    char *str = my_getenv(env, "PWD");
    int k = 0;

    if (my_getenv(env, "USER") == NULL || str == NULL) {
        isatty(0) == 1 ?
        my_putstr("\033[1;32m[mysh@localhost ~]$\033[1;37m ") : 0;
        return;
    }
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            k = i;
    k++;
    isatty(0) == 1 ? my_printf("\033[1;32m[%s@localhost %s]$\033[1;37m ",
    my_getenv(env, "USER"), k > 1 ? &str[k] : "~") : 0;
}

int set_cmd(char **tab, int *operator, char **env, int *save_std)
{
    static char **tmp;
    static int k = 0;
    int status = 0;

    set_pipe(operator);
    tab = set_redirection(operator, tab, tmp);
    if (operator[OUT] > 2) {
        tmp = tab;
        return 0;
    }
    k += get_cmd(tab, env);
    if (operator[OUT] == SEMICOLON || operator[OUT] == END)
        for (; k > 0; k--)
            seg_fault(status);
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
    buffer = strtok(buffer, ";|><&\n");
    for (int i = 0; buffer != NULL; i++) {
        tab = my_str_to_word_array(buffer);
        tab = globbing(tab);
        set_cmd(tab, &operator[i], env, save_std);
        buffer = strtok(NULL, ";|><&\n");
    }
    return 0;
}

static bool special_char(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '`' || str[i] == '(' || str[i] == '\\' || str[i] == '$')
            return (true);
    return (false);
}

int my_sh(char **env)
{
    size_t bufsize = 0;
    char *buffer = NULL;

    my_prompt(env);
    while (getline(&buffer, &bufsize, stdin) != -1) {
        update_history(buffer);
        special_char(buffer) == true ? sys_exec(buffer) :
        exec_cmd(buffer, env);
        my_prompt(env);
    }
    return 0;
}