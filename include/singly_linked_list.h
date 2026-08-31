#pragma once
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int val) : val(val), next(nullptr) {}
  ListNode(int val, ListNode *next) : val(val), next(next) {}
};

inline ListNode *arrayToLinkedList(const std::vector<int> &nums) {
  ListNode *head = new ListNode();
  ListNode *curr = head;
  for (const int &x : nums) {
    curr->next = new ListNode(x);
    curr = curr->next;
  }
  return head->next;
}

inline std::vector<int> linkedListToArray(ListNode *head) {
  std::vector<int> nums;
  ListNode *curr = head;
  while (curr != nullptr) {
    nums.push_back(curr->val);
    curr = curr->next;
  }
  return nums;
}

inline void printLinkedList(ListNode *head) {
  ListNode *curr = head;
  std::cout << "[";
  while (curr != nullptr) {
    if (curr != head)
      std::cout << ", ";
    std::cout << curr->val;
    curr = curr->next;
  }
  std::cout << "]" << std::endl;
}
