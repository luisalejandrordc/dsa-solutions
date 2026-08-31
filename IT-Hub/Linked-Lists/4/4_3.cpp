#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

// Reverse Linked List without creating new ListNode objects
// Tradeoff: You are modifying the original Linked List
ListNode *reverseLinkedList(ListNode *head) {
  ListNode *reve = nullptr;
  ListNode *head_next;
  while (head != nullptr) {
    head_next = head->next;
    head->next = reve;
    reve = head;
    head = head_next;
  }
  return reve;
}

bool isPalindrome(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  slow->next = reverseLinkedList(slow->next);
  slow = slow->next;
  while (slow != nullptr) {
    if (slow->val != head->val)
      return false;
    slow = slow->next;
    head = head->next;
  }
  return true;
}

int main() {
  printTitle("Palindrome Linked List");
  vector<int> nums = {1, 2, 3, 2, 1};
  ListNode *head = arrayToLinkedList(nums);
  printLinkedList(head);
  string solution = isPalindrome(head) ? "True" : "False";
  printLinkedList(head);
  cout << "Solution: " << solution << endl;
  return 0;
}
