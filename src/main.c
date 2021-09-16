/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "minishell.h"

int main(int ac, char **av __attribute__((unused)), char **env)
{
    if (ac != 1 || env[0] == NULL)
        return 84;
    return my_sh(env);
}
