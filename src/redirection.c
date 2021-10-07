/*
** EPITECH PROJECT, 2021
** redirection
** File description:
** redirection
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

int set_redirection(int *operator, char ***tab, char ***tmp)
{
    int fd = 0;

    if (operator[IN] == 3)
        fd = open(*tab[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (operator[IN] == 4 || operator[IN] == 6 || operator[IN] == 5)
        fd = open(*tab[0], O_RDWR | O_CREAT | O_APPEND, 0664);
    if (operator[IN] == 3 || operator[IN] == 4)
        dup2(fd, STDOUT_FILENO);
    if (operator[IN] == 5 || operator[IN] == 6)
        dup2(fd, STDIN_FILENO);
    if (operator[IN] > 2 && operator[IN] < 7) {
        close(fd);
        *tab = *tmp;
    }
    if (operator[OUT] > 2 && operator[OUT] < 7) {
        *tmp = *tab;
        return 1;
    }
    return 0;
}