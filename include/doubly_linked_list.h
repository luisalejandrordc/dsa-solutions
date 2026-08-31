#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

struct DListNode {
  int val;
  DListNode *next;
  DListNode *prev;
  DListNode() : val(0), next(nullptr), prev(nullptr) {}
  DListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
  DListNode(int x, DListNode *n, DListNode *p) : val(x), next(n), prev(p) {}
};

inline DListNode *arrayToDLinkedList(const std::vector<int> &nums) {
  DListNode *dummy = new DListNode();
  DListNode *curr = dummy;
  for (const int &x : nums) {
    curr->next = new DListNode(x, nullptr, curr);
    curr = curr->next;
  }
  return dummy->next;
}

inline std::vector<int> dLinkedListToArray(DListNode *start, bool goNext = 1) {
  std::vector<int> nums;
  DListNode *curr = start;
  while (curr != nullptr) {
    nums.push_back(curr->val);
    if (goNext)
      curr = curr->next;
    else
      curr = curr->prev;
  }
  return nums;
}

inline void printDLinkedList(DListNode *start, bool goNext = 1) {
  DListNode *curr = start;
  std::cout << "{";
  while (curr != nullptr) {
    if (curr != start)
      std::cout << ", ";
    std::cout << curr->val;
    if (goNext)
      curr = curr->next;
    else
      curr = curr->prev;
  }
  std::cout << "}" << std::endl;
}
