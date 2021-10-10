/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** which
*/

#include "minishell.h"
#include "my.h"
#include <fcntl.h>
#include <unistd.h>

int cmdwhich(char **strcmd, char **env __attribute__((unused)))
{
    int size = 0;

    for (; strcmd[size]; ++size);
    if (size < 2)
        return my_putstr("which: Too few arguments.\n");
    return 0;
}