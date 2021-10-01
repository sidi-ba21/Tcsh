/*
** EPITECH PROJECT, 2021
** exit
** File description:
** exit
*/

#include <stdlib.h>
#include "my.h"

int cmdexit(char **strcmd, char **env)
{
    (void) env;
    if (strcmd[0] && my_strcmp("exit", strcmd[0]) == 0) {
        my_putstr("exit\n");
        exit(0);
    }
    return 0;
}