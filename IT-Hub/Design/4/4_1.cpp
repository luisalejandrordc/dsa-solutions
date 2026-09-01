#include "../../../include/utils.h"
#include <utility>
#include <vector>

class ParkingSystem {
  // parkingSlots[i] = {#used, #total} for carType i+1
  std::array<std::pair<int, int>, 3> parkingSlots;

public:
  ParkingSystem(int b, int m, int s)
      : parkingSlots({{{0, b}, {0, m}, {0, s}}}) {}

  bool addCar(int carType) {
    std::pair<int, int> &foo = parkingSlots[carType - 1];
    if (foo.first == foo.second)
      return false;
    foo.first++;
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
