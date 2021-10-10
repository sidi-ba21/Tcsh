/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** where
*/

#include "minishell.h"
#include <builtinslist.h>
#include "my.h"
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static void check_builtins(char *str)
{
    for (int j = 0; j < 67; j++) {
        if (my_strcmp(builtins[j], str) == 0) {
            my_printf("%s is a shell built-in\n", str);
            return ;
        }
    }
    return ;
}

int cmdwhere(char **strcmd, char **env __attribute__((unused)))
{
    int size = 0;

    for (; strcmd[size]; ++size);
    if (size < 2)
        return my_putstr("where: Too few arguments.\n");
    for (int i = 1; i != size; i++) {
        check_builtins(strcmd[i]);
        (open(my_strcat("/usr/bin/", strcmd[i]), O_RDONLY) != -1) ?
        my_printf("/usr/bin/%s\n", strcmd[i]) : i;
        (open(my_strcat("/bin/", strcmd[i]), O_RDONLY) != -1) ?
        my_printf("/bin/%s\n", strcmd[i]) : i;
    }
    return 0;
}