#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

bool hasCycle(ListNode *head) {
  ListNode *curr = head;
  unordered_set<ListNode *> nodes = {curr};
  while (curr != nullptr) {
    if (nodes.count(curr->next))
      return true;
    nodes.insert(curr);
    curr = curr->next;
  }
  return false;
}

int main() {
  printTitle("Linked List Cycle");
  vector<int> nums = {1, 2, 3, 4, 5};
  ListNode *head = arrayToLinkedList(nums);
  ListNode *curr = head;
  while (true) {
    if (curr->next == nullptr) {
      curr->next = head;
      break;
    }
    curr = curr->next;
  }
  // printLinkedList(head);
  cout << "Solution: " << hasCycle(head) << endl;
  return 0;
}
