#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

int getListLength(ListNode *head) {
  int count = 0;
  while (head != nullptr) {
    head = head->next;
    count++;
  }
  return count;
}

ListNode *removeNthFromEnd(ListNode *head, int n) {
  int len = getListLength(head);
  if (len == n)
    return head->next;
  ListNode *curr = head;
  for (int i = 0; i < len - n - 1; i++)
    curr = curr->next;
  if (n == 1)
    curr->next = nullptr;
  else
    curr->next = curr->next->next;
  return head;
}

int main() {
  printTitle("Remove Nth Node From End of List");
  vector<int> nums = {1, 2, 3, 4, 5};
  ListNode *head = arrayToLinkedList(nums);
  cout << "Solution: ";
  printLinkedList(removeNthFromEnd(head, 2));
  return 0;
}
