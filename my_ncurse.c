/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** ncurse
*/

#include "minishell.h"
#include <curses.h>

void my_ncurse(void)
{
    static int x = 0;
    static int y = 0;
    WINDOW *win = initscr();
    int ch = getch();

    getyx(win, y, x);
    setsyx(y, x);
    move(y, x);

    if (ch == KEY_RIGHT) {
        y++;
        setsyx(y, x);
    }
    if (ch == KEY_LEFT) {
        y--;
        setsyx(y, x);
    }
}