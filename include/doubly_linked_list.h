#pragma once

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

inline void printDLinkedList()
