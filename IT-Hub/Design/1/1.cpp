#include "../../../include/utils.h"
#include <iostream>
#include <unordered_map>
#include <utility>

// Doubly Linked List
struct DListNode {
  int val;
  DListNode *next;
  DListNode *prev;
  DListNode() : val(0), next(nullptr), prev(nullptr) {}
  DListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
  DListNode(int x, DListNode *n, DListNode *p) : val(x), next(n), prev(p) {}
};

class LRUCache {
  // cache -> {key, {node address, value}}
  std::unordered_map<int, std::pair<DListNode *, int>> cache;
  DListNode *head, *tail;
  int capacity;

public:
  LRUCache(int capacity) : capacity(capacity), head(nullptr), tail(nullptr) {}
  int get(int key) {
    // key does not exist
    if (cache.count(key) == 0)
      return -1;
    // key exists
    DListNode *curr = cache[key].first;
    if (curr->prev != nullptr || curr->next != nullptr) {
      if (curr->prev == nullptr)
        head = curr->next;
      else
        curr->prev->next = curr->next;
      if (curr->next != nullptr)
        curr->next->prev = curr->prev;
      tail = curr;
    }
    return cache[key].second;
  }
};

int main() {
  printTitle("LRU Cache");
  return 0;
}
