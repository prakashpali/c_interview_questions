/**
Given a pointer to the head node of a linked list, the task is to rotate the linked list.
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

static ll_node *ll_rotate_right(ll_node *head, int k)
{
    int len = 0;

    if((k == 0) || (head == NULL) || (head->next == NULL))
    {
        return head;
    }

    ll_node *curr = head;
    while(curr->next != NULL)
    {
        curr = curr->next;
        len++;
    }

    k = k % len;

    curr->next = head;
    curr = head;

    while(len-k)
    {
        curr = curr->next;
        ++k;
    }

    head = curr->next;

    curr->next = NULL;

    return head;
}

static ll_node *ll_rotate_left(ll_node *head, int k)
{
    int len = 0;

    if((k == 0) || (head == NULL) || (head->next == NULL))
    {
        return head;
    }

    ll_node *curr = head;
    while(curr->next != NULL)
    {
        curr = curr->next;
        len++;
    }

    k = k % len;

    curr->next = head;
    curr = head;

    while(--k)
    {
        curr = curr->next;
    }

    head = curr->next;

    curr->next = NULL;

    return head;
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

    int rotate = 3;

    printf("Using ll_rotate_right():\n");
    ll_head1 = ll_rotate_right(ll_head1, rotate);
    ll_display(ll_head1);

    printf("Using ll_rotate_left():\n");
    ll_head1 = ll_rotate_left(ll_head1, rotate);
    ll_display(ll_head1);

    printf("=====================================================\n");

    return 0;
}
