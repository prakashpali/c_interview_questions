/**
Implement a doubly linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_NODES (15)

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} ll_node;

ll_node *ll_head = NULL;

/**
 * Insert a new element into the stack.
 * Remember, since we have to modify the main list (ll_head),
 * we must accept double pointer here.
 * NULL<-4<->3<->2<->1->NULL
 */
static void ll_push(ll_node **head, int element)
{
    /* Allocate node */
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));

    /* Put in the data */
    new_node->data = element;

    /* Since we are adding to the top of stack. */
    new_node->prev = NULL;

    /* Add prev to head. */
    if(*head != NULL)
    {
        (*head)->prev = new_node;
    }

    /* Link the old list of the new node */
    new_node->next = (*head);

    /* Move the head to point to the new node */
    (*head) = new_node;
}

/**
 * Return the top element of the stack.
 * Remember, since we have to modify the main list (ll_head),
 * we must accept double pointer here.
 * NULL<-4<->3<->2<->1->NULL
 */
static void ll_pop(ll_node **head)
{
    ll_node *temp;

    /* If head is NULL, then stack is empty. */
    if (*head == NULL)
    {
        return;
    }

    temp = *head;
    *head = (*head)->next;
    (*head)->prev = temp->prev;
    memset(temp, 0, sizeof(ll_node));
    free(temp);
}

/**
 * Return the top element.
*/
static int ll_peek(ll_node *head)
{
    if(head != NULL)
    {
        return head->data;
    }

    return 0;

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
    ll_pop(&ll_head);
    printf("Element at the top is %d\n", ll_peek(ll_head));
    ll_display(ll_head);
    ll_pop(&ll_head);
    printf("Element at the top is %d\n", ll_peek(ll_head));
    ll_display(ll_head);

    return 0;
}
