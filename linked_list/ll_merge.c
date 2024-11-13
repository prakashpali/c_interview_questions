/**
Merge two lists, where both lists are in ascending order.
Output list should also be in ascending order.

Example:
Input:
List1: 5->10->15->40->NULL
List2: 2->3->20->NULL

Output:
List: 2->3->5->10->15->20->40->NULL

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


/** Enqueue an element from the list */
static void ll_enqueue(ll_node **ll_head, ll_node **ll_tail, ll_node *node)
{
    if(*ll_head == NULL)
    {
        *ll_head = node;
        *ll_tail = *ll_head;
    }
    else
    {
        (*ll_tail)->next = node;
        (*ll_tail) = (*ll_tail)->next;
    }

}

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

static ll_node *ll_merge(ll_node *node1, ll_node *node2)
{
    ll_node * ml_h = NULL;
    ll_node * ml_t = NULL;

    ll_node *temp;

    if((node1 == NULL)&& (node2 == NULL))
    {
        return NULL;
    }

    while((node1 != NULL) && (node2 != NULL))
    {
        if(node1->data < node2->data)
        {
            temp = node1->next;
            node1->next = NULL;
            ll_enqueue(&ml_h, &ml_t, node1);
            node1 = temp;
        }
        else
        {
            temp = node2->next;
            node2->next = NULL;
            ll_enqueue(&ml_h, &ml_t, node2);
            node2 = temp;
        }
    }

    while(node1 != NULL)
    {
        temp = node1->next;
        node1->next = NULL;
        ll_enqueue(&ml_h, &ml_t, node1);
        node1 = temp;
    }

    while(node2 != NULL)
    {
        temp = node2->next;
        node2->next = NULL;
        ll_enqueue(&ml_h, &ml_t, node2);
        node2 = temp;
    }

    return ml_h;
}


static ll_node *ll_merge_1(ll_node *node1, ll_node *node2)
{
    ll_node * ml_h = NULL;

    ll_node *temp, *temp_head;

    if((node1 == NULL)&& (node2 == NULL))
    {
        return NULL;
    }

    if(node1->data < node2->data)
    {
        ml_h = node1;
        node1 = node1->next;
    }
    else
    {
        ml_h = node2;
        node2 = node2->next;
    }

    temp_head = ml_h;

    while((node1 != NULL) && (node2 != NULL))
    {
        if(node1->data < node2->data)
        {
            temp = node1->next;
            node1->next = NULL;
            temp_head->next = node1;
            temp_head = temp_head->next;
            node1 = temp;
        }
        else
        {
            temp = node2->next;
            node2->next = NULL;
            temp_head->next = node2;
            temp_head = temp_head->next;
            node2 = temp;
        }
    }

    while(node1 != NULL)
    {
        temp = node1->next;
        node1->next = NULL;
        temp_head->next = node1;
        temp_head = temp_head->next;
        node1 = temp;
    }

    while(node2 != NULL)
    {
        temp = node2->next;
        node2->next = NULL;
        temp_head->next = node2;
        temp_head = temp_head->next;
        node2 = temp;
    }

    return ml_h;
}

int main()
{
    int iter;
    ll_node *merged_list1;

    for (iter = NUM_NODES; iter > 0; --iter)
    {
        ll_push(&ll_head1, iter);
        --iter;
        ll_push(&ll_head2, iter);
    }

    ll_display(ll_head1);
    ll_display(ll_head2);

    merged_list1 = ll_merge(ll_head1, ll_head2);
    ll_display(merged_list1);

    merged_list1 = ll_merge_1(ll_head1, ll_head2);
    ll_display(merged_list1);

    return 0;
}
