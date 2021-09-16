/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int test(int ac, char *buffer)
{
    buffer = strtok(buffer, "| \n");
    int pfd[2];
    int pfd2[2];
    int pid;

    pipe(pfd);
    pipe(pfd2);

    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0 && i == 0) {
            close(pfd[0]); /* close the unused read side */
            dup2(pfd[1], STDOUT_FILENO); /* connect the write side with stdout */
            close(pfd[1]);

            execlp(buffer, buffer, (char *)0);
            return 1;
        }
        if (pid == 0 && i == 1) {
            close(pfd[1]); /* close the unused write side */
            dup2(pfd[0], STDIN_FILENO); /* connect the read side with stdin */
            close(pfd[0]); /* close the read side */

            close(pfd2[0]);
            dup2(pfd2[1], STDOUT_FILENO);
            close(pfd2[1]);

            execlp(buffer, buffer, (char *) 0);
            printf("wc failed"); /* if execlp returns, it's an error */
            return 2;
        }
        if (pid == 0 && i == 2) {
            close(pfd2[1]);
            dup2(pfd2[0], STDIN_FILENO);
            close(pfd2[0]);

            execlp(buffer, buffer, (char *) 0);
            return 3;
        }
        if (pid != 0) {
            if (i == 1) {
                close(pfd[0]);
                close(pfd[1]);
            }
            if (i == 2) {
                close(pfd2[0]);
                close(pfd2[1]);
            }
            wait(NULL);
        }
        buffer = strtok(NULL, "| \n");
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    size_t bufsize = 0;
    char *buffer = NULL;

    printf("$> ");
    while (getline(&buffer, &bufsize, stdin) != -1) {
        test(ac, buffer);
        printf("$> ");
    }
    return 0;
}
