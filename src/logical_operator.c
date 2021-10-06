/*
** EPITECH PROJECT, 2021
** logical_operator
** File description:
** logical_operator
*/

#include "minishell.h"

bool logical_operator(int operator, int count, int stop, int *k)
{
    int seg = seg_fault();

    if (operator == AND && (seg > 0 || count == -1))
        stop = true;
    if (operator == OR && !(seg > 0 || count == -1))
        stop = true;
    if (operator == AND || operator == OR)
        count > -1 ? *k -= 1 : 0;
    return stop;
}