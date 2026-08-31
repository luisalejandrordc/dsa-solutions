#include "../../../include/utils.h"
#include <iostream>
#include <ostream>
#include <vector>

class HitCounter {
  std::vector<int> record;

  int findFirstGreaterThan(int target) {
    // find first record[i] > target
    int l = 0, r = record.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (record[mid] <= target)
        l = mid + 1;
      else
        r = mid;
    }
    return l;
  }

public:
  HitCounter() {}

  void hit(int timestamp) { record.push_back(timestamp); }

  int getHits(int timestamp) {
    int leftIndex = findFirstGreaterThan(timestamp - 300);
    int rightIndex = findFirstGreaterThan(timestamp);
    return std::max(rightIndex - leftIndex, 0);
  }
};

int main() {
  printTitle("Design Hit Counter");
  HitCounter counter = HitCounter();
  counter.hit(1);
  counter.hit(2);
  counter.hit(3);
  std::cout << "Timestamp: 4\tHits: " << counter.getHits(4) << std::endl;
  counter.hit(300);
  std::cout << "Timestamp: 300\tHits: " << counter.getHits(300) << std::endl;
  std::cout << "Timestamp: 301\tHits: " << counter.getHits(301) << std::endl;
  return 0;
}
