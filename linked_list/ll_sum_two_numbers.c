/**
 * To add two numbers whose digits are stored in linked lists.
 *
 * Case 1: Digits are Stored in Reverse Order (Standard LeetCode Approach)
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Explanation: 342 + 465 = 807
 * Output: 7 -> 0 -> 8
 *
 * Case 2: Digits are Stored in Forward Order (Actual "Number" Representation)
 * Input: (3 -> 4 -> 2) + (4 -> 6 -> 5)
 * Explanation: 342 + 465 = 807
 * Output: 8 -> 0 -> 7
 *
 * Case 3: Edge Cases (Uneven Lengths & Final Carry)
 * Input: (9 -> 9) + (1)
 * Explanation: 99 + 1 = 100
 * Output: 0 -> 0 -> 1
 */

#include "../utils.h"

typedef struct ll_node
{
    int data;
    struct ll_node *next;
}ll_node_t;

static void ll_add_node(ll_node_t **head, int data)
{
    ll_node_t *new_node = (ll_node_t *)malloc(sizeof(ll_node_t));

    if (NULL == new_node)
    {
        return;
    }

    new_node->data = data;
    new_node->next = *head;
    *head = new_node;

    return;
}

static void ll_print(ll_node_t *head)
{
    while(NULL != head)
    {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

static ll_node_t *ll_add(ll_node_t *head1, ll_node_t *head2)
{
    int num1 = 0, num2 = 0;
    int sum = 0;
    ll_node_t *ll_sum = NULL;

    while (NULL != head1 || NULL != head2)
    {
        if (NULL != head1)
        {
            num1 *= 10;
            num1 += head1->data;
            head1 = head1->next;
        }
        if (NULL != head2)
        {
            num2 *= 10;
            num2 += head2->data;
            head2 = head2->next;
        }
    }

    sum = num1 + num2;
    while(sum > 0)
    {
        ll_add_node(&ll_sum, sum%10);
        sum = sum/10;
    }

    return ll_sum;
}

int main()
{
    ll_node_t *l1 = NULL, *l2 = NULL;

    ll_add_node(&l1, 1);

    ll_print(l1);

    ll_add_node(&l2, 9);
    ll_add_node(&l2, 9);

    ll_print(l2);

    ll_print(ll_add(l1, l2));

    return 0;

}