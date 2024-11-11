/**
 * Create a linked list. Thats all. :)
 */

#include "../utils.h"

typedef struct node
{
    int data;
    struct node *next;
} ll_node;

ll_node *ll_head = NULL;

/* A utility function to add nodes to a linked list */
static void ll_add_node(ll_node **head, int element)
{
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = element;

    new_node->next = *head;

    *head = new_node;
}

/* A utility function to print a given linked list */
static void ll_print_list(ll_node *head)
{
    while (head != NULL)
    {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{

    for (int iter = 0; iter < 5; iter++)
    {
        ll_add_node(&ll_head, iter);
    }

    printf("=====================================================\n");
    ll_print_list(ll_head);
    printf("=====================================================\n");

    return 0;
}
