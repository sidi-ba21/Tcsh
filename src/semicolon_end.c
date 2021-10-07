/*
** EPITECH PROJECT, 2021
** semicolon
** File description:
** handle semicolon and end
*/

#include "minishell.h"

int semicolon_end(int operator, bool *stop)
{
    if (operator == SEMICOLON || operator == END) {
        *stop = false;
        while (seg_fault() > 0);
    }
    return 0;
}