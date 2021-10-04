/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "minishell.h"

int main(int ac, char **av __attribute__((unused)), char **env)
{
    if (ac != 1)
        return 84;
    if (*env == NULL)
        env = create_env();
    return my_sh(env);
}
