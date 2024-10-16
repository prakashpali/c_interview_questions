/**
 * Implement a queue using LL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_NODES (15)

typedef struct node
{
    int data;
    struct node *next;
} ll_node;

ll_node *ll_head = NULL;
ll_node *ll_tail = NULL;

/** Enqueue an element from the list */
static void ll_enqueue(ll_node **ll_head, ll_node **ll_tail, int item)
{
    /* Allocate node */
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));

    /* Put in the data */
    new_node->data = item;
    new_node->next = NULL;

    if(*ll_head == NULL)
    {
        *ll_head = new_node;
        *ll_tail = *ll_head;
    }
    else
    {
        (*ll_tail)->next = new_node;
        (*ll_tail) = (*ll_tail)->next;
    }

}

/** Dequeue an element from the list */
static void ll_dequeue(ll_node **ll_head, ll_node **ll_tail)
{
    ll_node *tmp;

    tmp = *ll_head;
    *ll_head = (*ll_head)->next;
    memset(tmp, 0, sizeof(ll_node));
    free(tmp);
}

/** Print a given linked list */
static void ll_display(ll_node *head)
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
    int iter;
    ll_node *node;

    for (iter = NUM_NODES; iter > 0; --iter)
    {
        ll_enqueue(&ll_head, &ll_tail, iter);
    }

    ll_display(ll_head);
    ll_dequeue(&ll_head, &ll_tail);
    ll_display(ll_head);
    ll_dequeue(&ll_head, &ll_tail);
    ll_display(ll_head);

    return 0;
}
