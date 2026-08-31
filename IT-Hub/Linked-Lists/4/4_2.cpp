#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

ListNode *reverseList(ListNode *head) {
  ListNode *reve = nullptr;
  while (head != nullptr) {
    reve = new ListNode(head->val, reve);
    head = head->next;
  }
  return reve;
}

bool isPalindrome(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  ListNode *reve = reverseList(slow->next);
  while (reve != nullptr) {
    if (reve->val != head->val)
      return false;
    reve = reve->next;
    head = head->next;
  }
  return true;
}

int main() {
  printTitle("Palindrome Linked List");
  vector<int> nums = {1, 2, 3, 3, 1};
  ListNode *head = arrayToLinkedList(nums);
  printLinkedList(head);
  string solution = isPalindrome(head) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
