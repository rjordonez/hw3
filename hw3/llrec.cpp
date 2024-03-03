#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void deleteNode(Node* node) {
    delete node;
}


void addNode(Node*& head, Node* node) {
    node->next = head;
    head = node;
}
void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: if head is NULL, both smaller and larger lists are also NULL
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    // Recursive case: process the next node
    llpivot(head->next, smaller, larger, pivot);

    // Now decide where to add the current node (head)
    if (head->val <= pivot) {
        // Add to the smaller list and maintain the relative order
        addNode(smaller, head);
    } else {
        // Add to the larger list and maintain the relative order
        addNode(larger, head);
    }

    // Set the head to NULL since the original list should not be preserved
    head = NULL;
}
