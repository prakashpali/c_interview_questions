/**
Given a pointer to the head node of a linked list, the task is to print Nth node from right of the linked list.
*/

#include "../utils.h"

#define NUM_NODES (15)

typedef struct node
{
    int data;
    struct node *next;
} ll_node;

ll_node *ll_head1 = NULL;

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

/** Print a given linked list */
static void ll_display(ll_node *head)
{
    while (head != NULL)
    {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n\n");
}

static void ll_print_nth_from_right(ll_node *head, int N)
{
    int len = 0;

    if((N == 0) || (head == NULL) || (head->next == NULL))
    {
        return;
    }

    ll_node *curr = head, *temp = head;
    while(--N)
    {
        temp = temp->next;
    }

    while(temp->next != NULL)
    {
        curr = curr->next;
        temp = temp->next;
    }

    printf("Nth node from right is %d\n", curr->data);
}

int main()
{
    int iter;

    for (iter = NUM_NODES; iter > 0; --iter)
    {
        ll_push(&ll_head1, iter);
    }

    printf("=====================================================\n");

    ll_display(ll_head1);

    int N = 3;

    printf("Using ll_print_nth_from_right():\n");
    ll_print_nth_from_right(ll_head1, N);

    printf("=====================================================\n");

    return 0;
}
