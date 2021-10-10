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
int disp_hist(char **strcmd, char **env);
int cmdunsetenv(char **strcmd, char **env);
int unset_loc(char **strcmd, char **env);
int set_loc(char **strcmd, char **env);
int update_alias(char **strcmd, char **env);
int cmdrepeat(char **strcmd, char **env);
int cmdwhich(char **cmd, char **env);
int cmdwhere(char **cmd, char **env);

typedef struct comand
{
    char *cmd1;
    int (*cmd2)(char **, char **);
} cmd;

static const cmd tabcmd[] =
{
    {"cd", &cmdcd},
    {"env", &cmdenv},
    {"setenv", &cmdsetenv},
    {"unsetenv", &cmdunsetenv},
    {"set", &set_loc},
    {"unset", &unset_loc},
    {"which", &cmdwhich},
    {"where", &cmdwhere},
    {"history", &disp_hist},
    {"alias", &update_alias},
    {"repeat", &cmdrepeat},
    {NULL, 0},
};

typedef struct operator_s
{
    char *sep;
    int op;
}operator_t;

typedef enum operator {
    END = 0,
    SEMICOLON,
    PIPE,
    REDIRECTION_OUT1,
    REDIRECTION_OUT2,
    REDIRECTION_IN1,
    REDIRECTION_IN2,
    OR,
    AND,
}operator;

static const operator_t tabop[] =
{
    {";", SEMICOLON},
    {"|", PIPE},
    {">", REDIRECTION_OUT1},
    {">>", REDIRECTION_OUT2},
    {"<", REDIRECTION_IN1},
    {"<<", REDIRECTION_IN2},
    {"&&", AND},
    {"||", OR},
    {NULL, 0},
};

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