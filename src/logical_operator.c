/*
** EPITECH PROJECT, 2021
** logical_operator
** File description:
** logical_operator
*/

#include "minishell.h"

int logical_operator(int operator, int count, bool *stop)
{
    if (operator == AND && (seg_fault() > 0 || count == -1))
        *stop = true;
    if (operator == OR && !(seg_fault() > 0 || count == -1))
        *stop = true;
    return 0;
}