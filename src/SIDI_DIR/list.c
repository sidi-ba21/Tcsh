/*
** EPITECH PROJECT, 2021
** list.c
** File description:
** list.c
*/

#include "minishell.h"

list_t *push(list_t **head, char *new_data)
{
    list_t *last = NULL;
    list_t *new_node = (list_t *)
        malloc(sizeof(list_t));

    if (*head == NULL) {
        new_node->data = my_strdup(new_data);
        new_node->next = new_node->prev = new_node;
        (*head) = new_node;
        return (*head);
    }
    last = (*head)->prev;
    new_node->data = my_strdup(new_data);
    new_node->next = (*head);
    (*head)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
    return (*head);
}

list_t *params_to_list(char *const *tab)
{
    list_t *list = NULL;

    for (int i = 0; tab[i]; i++)
        list = push(&list, tab[i]);
    return (list);
}

list_t *add_to_list(list_t *list, char *str)
{
    list = push(&list, str);
    return (list);
}

int printlist(list_t *head)
{
    list_t *tmp = head;

    if (head == NULL) {
        my_putstr("list is empty\n");
        return (0);
    }
    do {
        my_printf("%s\n", head->data);
        head = head->next;
    } while (head != tmp);
    return (0);
}

list_t *del_node(list_t **list, char *str)
{
    list_t *ptr = (*list)->prev;
    list_t *tmp = (*list);

    do {
        if (my_strncmp((*list)->data, str, my_strlen(str)) == 0) {
            if ((*list) == (*list)->next)
                (*list) = NULL;
            else {
                ptr->next = (*list)->next;
                ptr->next->prev = ptr;
                *list = (*list)->next;
            }
        }
        (*list) = (*list)->next;
        ptr = ptr->next;
    } while ((*list) != tmp);
    return (*list);
}