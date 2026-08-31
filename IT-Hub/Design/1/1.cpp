#include "../../../include/doubly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <utility>

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
    auto [curr, value] = cache[key];
    if (curr != tail) {
      // remove curr from the list
      if (curr == head)
        head = curr->next;
      else
        curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      // move curr to the end
      tail->next = curr;
      curr->prev = tail;
      curr->next = nullptr;
      tail = curr;
    }
    return value;
  }

  void put(int key, int value) {
    // key exists
    if (cache.count(key) == 1) {
      DListNode *curr = cache[key].first;
      cache[key] = {curr, value};
      get(key);
      return;
    }

    // key does not exist and cache is not full
    if (cache.size() < capacity) {
      DListNode *curr = new DListNode(key);
      if (cache.empty()) {
        head = curr;
        tail = curr;
      } else {
        tail->next = curr;
        curr->prev = tail;
        tail = curr;
      }
      cache[key] = {curr, value};
      return;
    }

    // key does not exist and cache is full
    cache.erase(head->val);
    cache[key] = {head, value};
    get(key);
  }
};

int main() {
  printTitle("LRU Cache");
  LRUCache myCache = LRUCache(2);
  myCache.put(1, 1);
  myCache.put(2, 2);
  std::cout << "Key: 1 \t Value: " << myCache.get(1) << std::endl;
  myCache.put(3, 3);
  std::cout << "Key: 2 \t Value: " << myCache.get(2) << std::endl;
  myCache.put(4, 4);
  std::cout << "Key: 1 \t Value: " << myCache.get(1) << std::endl;
  std::cout << "Key: 3 \t Value: " << myCache.get(3) << std::endl;
  std::cout << "Key: 4 \t Value: " << myCache.get(4) << std::endl;
  return 0;
}
