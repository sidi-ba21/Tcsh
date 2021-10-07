/*
** EPITECH PROJECT, 2021
** semicolon
** File description:
** handle semicolon and end
*/

#include "minishell.h"

int semicolon_end(int operator, bool *stop)
{
    int stat_loc = 0;

    if (operator == SEMICOLON || operator == END) {
        *stop = false;
        while (seg_fault(&stat_loc) > 0);
    }
    return 0;
}