/**
 * Detect loop in a linked list.
 */

#include "../utils.h"

typedef struct node
{
    int data;
    struct node *next;
} ll_node;

/* A utility function to create a node */
static ll_node *ll_create_node(int element)
{
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->data = element;

    new_node->next = NULL;

    return new_node;
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

static bool has_loop(ll_node *head)
{
    bool ret = false;
    ll_node *fast = head;
    ll_node *slow = head;

    while((fast != NULL) && (fast->next != NULL) && (slow != NULL))
    {
        fast = fast->next->next;
        slow = slow->next;

        if (slow == fast)
        {
            ret = true;
            break;
        }
    }

    return ret;
}

int main()
{

    ll_node *ll_head1 = ll_create_node(1);
    ll_head1->next = ll_create_node(2);
    ll_head1->next->next = ll_create_node(3);
    ll_head1->next->next->next = ll_create_node(4);
    ll_head1->next->next->next->next = ll_create_node(5);
    ll_head1->next->next->next->next->next = ll_create_node(6);
    ll_head1->next->next->next->next->next->next = ll_head1;

    ll_node *ll_head2 = ll_create_node(1);
    // ll_head2->next = ll_create_node(2);
    // ll_head2->next->next = ll_create_node(3);
    // ll_head2->next->next->next = ll_create_node(4);
    // ll_head2->next->next->next->next = ll_create_node(5);
    // ll_head2->next->next->next->next->next = ll_create_node(6);

    printf("=====================================================\n");

    if (has_loop(ll_head1))
    {
        printf("Loop detected\n");
    }
    else
    {
        printf("Loop NOT detected\n");
    }

    if (has_loop(ll_head2))
    {
        printf("Loop detected\n");
    }
    else
    {
        printf("Loop NOT detected\n");
    }

    printf("=====================================================\n");

    return 0;
}
