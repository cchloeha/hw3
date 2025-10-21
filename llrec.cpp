#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
  if(head == NULL) {
    // On base case, make sure outputs are clean
    smaller = NULL;
    larger = NULL;
    return;
  }

  // Save current and advance recursion on the rest first
  Node* curr = head;
  Node* next = head->next;

  llpviot(next, smaller, larger, pivot);

  // Detach curr
  curr->next = NULL;

  // Insert curr at front of appropriate list. Because we recursed to tail first, prepending here preserves original order overall
  if(curr->val <= pivot) {
    curr->next = smaller;
    smaller = curr;
  }
  else {
    curr->next = larger;
    larger = curr;
  }
  // Original list should be empty when done
  head = NULL;
}


