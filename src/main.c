/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "minishell.h"

void my_prompt(char **env)
{
    char *str = my_getenv(env, "PWD");
    int k = 0;

    if (my_getenv(env, "USER") == NULL || str == NULL) {
        isatty(0) == 1 ? my_printf("\033[1;32m[mysh@localhost ~]$\033[1;37m ") : 0;
        return;
    }
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            k = i;
    k++;
    isatty(0) == 1 ? my_printf("\033[1;32m[%s@localhost %s]$\033[1;37m ",
    my_getenv(env, "USER"), k > 1 ? &str[k] : "~") : 0;
}

char **create_env(void)
{
    size_t size = 0;
    char *buf = NULL;
    char **tmp = malloc(sizeof(char *) * 4);

    tmp[0] = my_strdup("PWD=");
    tmp[0] = my_strcat(tmp[0], getcwd(buf, size));
    tmp[1] = my_strdup("HOST=localhost.localdomain");
    tmp[2] = my_strdup("PATH=/usr/bin:/bin");
    tmp[3] = 0;
    free(buf);
    return (tmp);
}

int main(int ac, char **av __attribute__((unused)), char **env)
{
    if (ac != 1)
        return 84;
    if (env[0] == NULL)
        env = create_env();
    return my_sh(env);
}
