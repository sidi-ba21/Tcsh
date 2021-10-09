/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** var_interpreter
*/

#include "my.h"
#include "minishell.h"

int is_alpha(char *str, bool chr_eq)
{
    if (!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a' && str[0] <= 'z'))
        return (1);
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] != '=' && str[i] != '_' && ((str[i] >= '!' && str[i] < '0')
        || (str[i] >= ':' && str[i] < 'A') || (str[i] >= '[' && str[i] <= '_')
        || str[i] > 'z'))
            return (2);
        if (str[i] == '=' && chr_eq == true)
            return (2);
    }
    return (0);
}

char *modify_str(char *str)
{
    char *tmp = malloc(sizeof(char) * (my_strlen(str) + 4) * 3);
    int j = 0;
    char ptr[7] = "status";

    for (int i = 0; str[i] != '\0'; i++, j++) {
        if (str[i] == '$' && str[i + 1] == '?') {
            tmp[j++] = '$';
            for (int k = 0; k < 6; k++, j++)
                tmp[j] = ptr[k];
            j--;
            i++;
        }
        else
            tmp[j] = str[i];
    }
    tmp[j] = '\0';
    return (tmp);
}

int set_loc(char **cmd, char **env)
{
    int error = 0;

    (void)env;
    if (cmd[1] == NULL)
        return system(cmd[0]);
    for (int i = 1; cmd[i]; i++) {
        error = is_alpha(cmd[i], false);
        if (error == 1)
            return (my_errorstr("set: Variable name must begin "),
            my_errorstr("with a letter.\n"));
        else if (error == 2)
            return (my_errorstr("set: Variable name must contain "),
            my_errorstr("alphanumeric characters.\n"));
        else
            putenv(cmd[i]);
    }
    return (0);
}

int unset_loc(char **cmd, char **env)
{
    if (cmd[1] == NULL)
        return (my_errorstr("unset: Too few arguments.\n"));
    for (int i = 0; cmd[i]; i++)
        my_getenv(env, cmd[i]) == NULL ? unsetenv(cmd[i]) : 0;
    return (0);
}