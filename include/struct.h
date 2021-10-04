/*
** EPITECH PROJECT, 2021
** struct.h
** File description:
** struct.h
*/

int cmdcd(char **strcmd, char **env);
int cmdexit(char **strcmd, char **env);
int cmdenv(char **strcmd, char **env);
int my_setenv(char **strcmd, char **env);
int cmdsetenv(char **strcmd, char **env);
int cmdunsetenv(char **strcmd, char **env);

typedef struct comand
{
    char *cmd1;
    int (*cmd2)(char **, char **);
}cmd;

static const cmd tabcmd[4] =
{
    {"cd", &cmdcd},
    {"env", &cmdenv},
    {"setenv", &cmdsetenv},
    {"unsetenv", &cmdunsetenv},
};

typedef enum operator_s {
    END = 0,
    SEMICOLON,
    PIPE,
    REDIRECTION_OUT1,
    REDIRECTION_OUT2,
    REDIRECTION_IN1,
    REDIRECTION_IN2,
}operator_t;

typedef enum port_s {
    IN = 0,
    OUT,
    ERR,
}port_t;

typedef struct linked_list_t
{
    char const *data;
    struct linked_list_t *next;
}l_list;