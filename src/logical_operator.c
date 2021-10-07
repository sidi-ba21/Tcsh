/*
** EPITECH PROJECT, 2021
** logical_operator
** File description:
** logical_operator
*/

#include "minishell.h"

int logical_operator(int operator, int count, bool *stop)
{
    int stat_loc = 0;

    if (operator == AND) {
        seg_fault(&stat_loc);
        *stop = stat_loc > 0 || count == -1 ? true : *stop;
    }
    if (operator == OR) {
        seg_fault(&stat_loc);
        *stop = stat_loc > 0 || count == -1 ? *stop : true;
    }
    return 0;
}