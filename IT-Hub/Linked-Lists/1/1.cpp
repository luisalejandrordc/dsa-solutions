#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

ListNode *reverseLinkedList(ListNode *head) {
  ListNode *curr = head;
  ListNode *reve = nullptr;
  while (curr != nullptr) {
    reve = new ListNode(curr->val, reve);
    curr = curr->next;
  }
  return reve;
}

int main() {
  printTitle("Reverse a Linked List");
  vector<int> nums = {1, 2, 3, 4, 5};
  ListNode *head = arrayToLinkedList(nums);
  ListNode *reve = reverseLinkedList(head);
  cout << "Solution: ";
  printLinkedList(reve);
  return 0;
}
