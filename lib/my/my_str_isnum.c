/*
** EPITECH PROJECT, 2020
** str isnum
** File description:
** f
*/

int my_str_isnum(char const *str)
{
    if (!(str[0] == '-' || str[0] == '+' || (str[0] >= '0' && str[0] <= '9')))
        return (0);
    for (int i = 1; str[i]; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
    }
    return (1);
}
