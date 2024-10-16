/**
Given a singly linked list, find the middle of the linked list.
For example, if the given linked list is 1->2->3->4->5 then the output should be 3.
If there are even nodes, then there would be two middle nodes, we need to print the second middle element.
For example, if the given linked list is 1->2->3->4->5->6 then the output should be 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_NODES (15)

typedef struct node
{
    int data;
    struct node *next;
}ll_node;

ll_node *ll_head = NULL;

void ll_add_node(ll_node **head, int new_data)
{
    /* Allocate node */
    ll_node* new_node =
        (ll_node*) malloc(sizeof(ll_node));

    /* Put in the data */
    new_node->data = new_data;

    /* Link the old list of the new node */
    new_node->next = (*head);

    /* Move the head to point to the new node */
    (*head) = new_node;
}

/* A utility function to print a given linked list */
void ll_print_list(ll_node *head)
{
    while (head != NULL)
    {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int ll_get_len(ll_node *head)
{
    int len = 0;
    while (head != NULL)
    {
        head = head->next;
        ++len;
    }
    return len;
}

/* Get node at an index. */
ll_node *ll_get_node_at_index(ll_node *head, int index)
{
    if(index == 0)
    {
        return head;
    }

    while(head != NULL)
    {
        head = head->next;
        --index;
        if(!index)
        {
            break;
        }
    }
    return head;
}

/* Print data held by middle node of the list. */
void ll_print_middle(ll_node *head)
{
    int middle_index;
    ll_node *node_at_index;

    middle_index = ll_get_len(ll_head)/2;
    node_at_index = ll_get_node_at_index(ll_head, middle_index);
    if(node_at_index != NULL)
    {
        printf("Data at the index %d is: %d\n", middle_index, node_at_index->data);
    }
    else
    {
        printf("Nothing at the index.\n");
    }
}

/* Print data held by middle node of the list. Optimized solution. */
void ll_print_middle_1(ll_node *head)
{
    ll_node *middle_node = head;
    int count = 0;
    int middle_index = 0;

    while(head != NULL)
    {
        if(count & 1)
        {
            ++middle_index;
            middle_node = middle_node->next;
        }

        head = head->next;
        ++count;
    }

    if(middle_node != NULL)
    {
        printf("Data at the index %d is: %d\n", middle_index, middle_node->data);
    }
    else
    {
        printf("Nothing in list.\n");
    }
}

int main()
{
    int iter;

    for (iter = NUM_NODES; iter > 0; --iter)
    {
        ll_add_node(&ll_head, iter);
    }

    printf("Length of list is: %d\n", ll_get_len(ll_head));

    ll_print_list(ll_head);
    ll_print_middle(ll_head);
    ll_print_middle_1(ll_head);

    return 0;
}

