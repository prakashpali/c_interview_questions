/**
Given a pointer to the head node of a linked list, the task is to reverse the linked list.
We need to reverse the list by changing the links between nodes.
Examples:
Input: Head of following linked list
1->2->3->4->NULL
Output: Linked list should be changed to,
4->3->2->1->NULL

Input: Head of following linked list
1->2->3->4->5->NULL
Output: Linked list should be changed to,
5->4->3->2->1->NULL
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

ll_node *ll_head1 = NULL;
ll_node *ll_head2 = NULL;

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
    printf("NULL\n");
}

static ll_node *ll_reverse(ll_node * head)
{
    /* Iterate over the list.
    * We need to change the current->next link to prev.
    */
    if((head == NULL) || (head->next == NULL))
    {
        return head;
    }

    ll_node *prev, *curr, *next;
    prev = NULL;
    curr = head;
    next = head->next;
    while(next != NULL)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }

    curr->next = prev;

    return curr;
}

int main()
{
    int iter;
    ll_node *reversed_list1;
    ll_node *reversed_list2;

    for (iter = NUM_NODES; iter > 1; --iter)
    {
        ll_push(&ll_head1, iter);
        --iter;
        ll_push(&ll_head2, iter);
    }

    ll_display(ll_head1);
    ll_display(ll_head2);

    reversed_list1 = ll_reverse(ll_head1);
    ll_display(reversed_list1);

    reversed_list2 = ll_reverse(ll_head2);
    ll_display(reversed_list2);

    return 0;
}
