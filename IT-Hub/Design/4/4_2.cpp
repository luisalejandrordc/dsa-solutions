#include "../../../include/utils.h"
#include <vector>

class ParkingSystem {
  // freeSlots[i] = free parking slots for carType i+1
  std::array<int, 3> freeSlots;

public:
  ParkingSystem(int b, int m, int s) : freeSlots({b, m, s}) {}

  bool addCar(int carType) {
    // save time by passing by reference
    int &slot = freeSlots[carType - 1];
    // no more free slots
    if (slot == 0)
      return false;
    // park car in its correspondent space
    slot--;
    return true;
  }
};

int main() {
  printTitle("Design Parking System");

  ParkingSystem ps = ParkingSystem(1, 1, 0);
  std::vector<int> parameters = {1, 2, 3, 1};
  std::vector<std::string> result;
  for (int i = 0; i < parameters.size(); i++)
    result.push_back(ps.addCar(parameters[i]) ? "True" : "False");
  printVector(result);

  return 0;
}
