/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example 1:

Input: head = [1,4,3,2,5,2], x = 3 Output: [1,2,2,4,3,5]

Example 2:

Input: head = [2,1], x = 2 Output: [1,2]


Constraints:

* The number of nodes in the list is in the range [0, 200].
* -100 <= Node.val <= 100
* -200 <= x <= 200
*/

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Partitions the linked list around a value x.
 * 
 * Time Complexity: O(N) where N is the number of nodes in the linked list.
 * Space Complexity: O(1) as we only use pointers to rearrange existing nodes.
 */
struct ListNode* partition(struct ListNode* head, int x) {
    // Create dummy nodes to hold the start of the 'less than x' and 'greater or equal to x' lists
    struct ListNode less_head = {0, NULL};
    struct ListNode greater_head = {0, NULL};
    
    // Pointers to build the two lists
    struct ListNode *less_ptr = &less_head;
    struct ListNode *greater_ptr = &greater_head;
    
    struct ListNode *curr = head;
    
    // Traverse the original list and distribute the nodes
    while (curr != NULL) {
        if (curr->val < x) {
            less_ptr->next = curr;
            less_ptr = less_ptr->next;
        } else {
            greater_ptr->next = curr;
            greater_ptr = greater_ptr->next;
        }
        curr = curr->next;
    }
    
    // IMPORTANT: Terminate the greater list to avoid cycles
    // (the last node in the greater list might originally have pointed to a node < x)
    greater_ptr->next = NULL;
    
    // Connect the end of the 'less' list to the start of the 'greater' list
    less_ptr->next = greater_head.next;
    
    // Return the head of the newly partitioned list
    return less_head.next;
}

// ---------------------------------------------------------
// Helper functions for testing
// ---------------------------------------------------------
struct ListNode* create_node(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

void print_list(struct ListNode* head) {
    printf("[");
    struct ListNode* curr = head;
    while (curr != NULL) {
        printf("%d", curr->val);
        if (curr->next != NULL) printf(",");
        curr = curr->next;
    }
    printf("]\n");
}

int main() {
    // Example 1: head = [1,4,3,2,5,2], x = 3 
    // Output should be: [1,2,2,4,3,5]
    struct ListNode* head1 = create_node(1);
    head1->next = create_node(4);
    head1->next->next = create_node(3);
    head1->next->next->next = create_node(2);
    head1->next->next->next->next = create_node(5);
    head1->next->next->next->next->next = create_node(2);
    
    printf("Example 1:\n");
    printf("Input: head = "); print_list(head1); printf("x = 3\n");
    struct ListNode* result1 = partition(head1, 3);
    printf("Output: "); print_list(result1);
    printf("\n");

    // Example 2: head = [2,1], x = 2 
    // Output should be: [1,2]
    struct ListNode* head2 = create_node(2);
    head2->next = create_node(1);
    
    printf("Example 2:\n");
    printf("Input: head = "); print_list(head2); printf("x = 2\n");
    struct ListNode* result2 = partition(head2, 2);
    printf("Output: "); print_list(result2);

    return 0;
}