/*
** EPITECH PROJECT, 2021
** env
** File description:
** env builting
*/

#include "my.h"

int cmdenv(char **strcmd __attribute__((unused)), char **env)
{
    return my_show_word_array(env);
}