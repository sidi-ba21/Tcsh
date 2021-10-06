/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** history
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "minishell.h"

static void my_free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
    return ;
}

static char **recup_hist(void)
{
    struct stat sts;
    char **tab = NULL;
    int fd = open(".hist", O_RDONLY);
    char *temp = NULL;

    stat(".hist", &sts);
    temp = malloc(sizeof(char) * (sts.st_size + 1));
    read(fd, temp, sts.st_size);
    tab = my_str_to_word_array_delim(temp, "\n");
    free(temp);
    return tab;
}

static int verify_syntax(char **strcmd)
{
    int tabsize = 0;

    for (; strcmd[tabsize]; ++tabsize);
    if (tabsize < 2)
        return 2;
    if (strcmd[1][0] == '-') {
        my_putstr("Usage: history [-chrSLMT] [# number of events].\n");
        return 1;
    }
    for (int i = 1; strcmd[1][i]; i++) {
        if (strcmd[1][i] < '0' || strcmd[1][i] > '9') {
            my_putstr("history: Badly formed number.\n");
            return 1;
        }
    }
    return 0;
}

int disp_hist(char **strcmd, char **env __attribute__((unused)))
{
    char **tab = NULL;
    int size = 0;
    int secu = verify_syntax(strcmd);
    int nb = 0;

    if (secu == 1)
        return 84;
    tab = recup_hist();
    if (secu == 2)
        return my_show_word_array(tab);
    nb = my_getnbr(strcmd[1]);
    for (; tab[size]; ++size);
    if (nb >= size) {
        my_show_word_array(tab);
    } else
        for (int i = size - nb; tab[i]; i++)
            my_printf("%s\n", tab[i]);
    my_free_tab(tab);
    return 0;
}

void update_history(char *cmd)
{
    static int pos = 1;
    int fd = open(".hist", O_RDWR | O_CREAT | O_APPEND, 0664);
    char *strpos = my_nbrtostr(pos);
    time_t t = time(NULL);
    struct tm tom = *localtime(&t);

    write(fd, "     ", 5);
    write(fd, strpos, my_strlen(strpos));
    write(fd, "  ", 2);
    write(fd, my_strcat(my_nbrtostr(tom.tm_hour), ":"),
    my_strlen(my_nbrtostr(tom.tm_hour)) + 1);
    write(fd, my_nbrtostr(tom.tm_min), my_strlen(my_nbrtostr(tom.tm_min)));
    write(fd, "   ", 3);
    write(fd, cmd, my_strlen(cmd));
    free(strpos);
    close(fd);
    pos += 1;
}