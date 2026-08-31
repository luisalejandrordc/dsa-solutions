#include "../../../include/singly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
  ListNode *head = new ListNode();
  ListNode *curr = head;
  while (list1 != nullptr && list2 != nullptr) {
    if (list1->val <= list2->val) {
      curr->next = new ListNode(list1->val);
      list1 = list1->next;
    } else {
      curr->next = new ListNode(list2->val);
      list2 = list2->next;
    }
    curr = curr->next;
  }
  while (list1 != nullptr) {
    curr->next = new ListNode(list1->val);
    list1 = list1->next;
    curr = curr->next;
  }
  while (list2 != nullptr) {
    curr->next = new ListNode(list2->val);
    list2 = list2->next;
    curr = curr->next;
  }
  return head->next;
}

int main() {
  printTitle("Merge Two Sorted Lists");
  vector<int> nums1 = {1, 2, 4};
  vector<int> nums2 = {1, 3, 4};
  ListNode *list1 = arrayToLinkedList(nums1);
  ListNode *list2 = arrayToLinkedList(nums2);
  printLinkedList(list1);
  printLinkedList(list2);
  cout << "Solution: ";
  ListNode *merged = mergeTwoLists(list1, list2);
  printLinkedList(merged);
  return 0;
}
