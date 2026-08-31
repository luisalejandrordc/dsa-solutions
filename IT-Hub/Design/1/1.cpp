#include "../../../include/doubly_linked_list.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

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
    head->val = key;
    get(key);
  }
};

int main() {
  printTitle("LRU Cache");
  std::cout << "Solution: " << std::endl;

  // testing
  LRUCache myCache = LRUCache(2);
  std::vector<std::string> methods = {"put", "put", "get", "put", "get",
                                      "put", "get", "get", "get"};
  std::vector<std::vector<int>> parameters = {{1, 1}, {2, 2}, {1}, {3, 3}, {2},
                                              {4, 4}, {1},    {3}, {4}};
  std::vector<std::optional<int>> result;
  for (int i = 0; i < methods.size(); i++) {
    if (methods[i] == "put") {
      myCache.put(parameters[i][0], parameters[i][1]);
      result.push_back(std::nullopt);
    } else {
      result.push_back(myCache.get(parameters[i][0]));
    }
  }
  printVector(result);

  return 0;
}
