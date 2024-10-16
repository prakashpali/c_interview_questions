/**
Delete a node whose data matches with a given element.
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

/**
 * Insert a new element into the stack.
 * Remember, since we have to modify the main list (ll_head),
 * we must accept double pointer here.
 */
static void ll_push(ll_node **head, int element)
{
    /* Allocate node */
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));

    /* Put in the data */
    new_node->data = element;

    /* Link the old list of the new node */
    new_node->next = (*head);

    /* Move the head to point to the new node */
    (*head) = new_node;
}

/**
 * Delete a node whose data matches with element.
*/
static void ll_delete_node(ll_node **head, int element)
{
    ll_node *prev;
    ll_node *curr;

    /* Check if data is present in head. */
    if((*head)->data == element)
    {
        curr = *head;
        (*head) = (*head)->next;
        memset((void*)curr, 0, sizeof(ll_node));
        free(curr);
        return;
    }

    prev = *head;
    curr = (*head)->next;

    while(curr != NULL)
    {
        if(curr->data == element)
        {
            prev->next = curr->next;
            memset((void*)curr, 0, sizeof(ll_node));
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
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
        ll_push(&ll_head, iter);
    }

    ll_display(ll_head);
    ll_delete_node(&ll_head, 1);
    ll_display(ll_head);
    ll_delete_node(&ll_head, 3);
    ll_display(ll_head);

    return 0;
}
