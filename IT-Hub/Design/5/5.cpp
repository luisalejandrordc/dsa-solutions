#include "../../../include/utils.h"
#include <array>
#include <random>
#include <unordered_map>

class Solution {
  std::unordered_map<std::string, std::string> longToShort;
  std::unordered_map<std::string, std::string> shortToLong;

  std::array<char, 62> characters = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
      'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
      'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c',
      'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
      'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int keyLength = 6;
  std::string shortUrlPrefix = "https://tinyurl.com/";

  // initialize the std Mersenne Twister engine with a random seed
  std::mt19937 gen{std::random_device{}()};
  // define the distribution range [inclusive, inclusive]
  std::uniform_int_distribution<int> distrib{0, 61};

  std::string generateUniqueKey() {
    std::string key(keyLength, ' ');
    do {
      for (char &c : key)
        c = characters[distrib(gen)];
    } while (shortToLong.count(key));

    return key;
  }

public:
  Solution() {}

  std::string encode(std::string longUrl) {
    if (auto it = longToShort.find(longUrl); it != longToShort.end())
      return shortUrlPrefix + it->second;
    std::string key = generateUniqueKey();
    longToShort[longUrl] = key;
    shortToLong[key] = longUrl;
    return shortUrlPrefix + key;
  }

  std::string decode(std::string shortUrl) {
    std::string key = shortUrl.substr(shortUrlPrefix.length());
    if (auto it = shortToLong.find(key); it != shortToLong.end())
      return it->second;
    return "";
  }
};

int main() {
  printTitle("Encode and Decode TinyURL");
  std::cout << "Solution:" << std::endl;

  Solution s = Solution();
  std::string shortUrl =
      s.encode("https://leetcode.com/problems/design-tinyurl");
  std::cout << shortUrl << std::endl;
  std::cout << s.decode(shortUrl) << std::endl;

  return 0;
}
