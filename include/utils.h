#pragma once
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

inline void printTitle(const std::string &title) {
  std::string border(title.length() + 10, '-');
  std::cout << border << std::endl;
  std::cout << "|    " << title << "    |" << std::endl;
  std::cout << border << std::endl;
}

// std::optional<T> condition
template <typename T> struct is_optional : std::false_type {};
template <typename T> struct is_optional<std::optional<T>> : std::true_type {};
template <typename T>
inline constexpr bool is_optional_v = is_optional<T>::value;

// std::pair<T1, T2> condition
template <typename T> struct is_pair : std::false_type {};
template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};
template <typename T> inline constexpr bool is_pair_v = is_pair<T>::value;

// std::vector<T> condition
template <typename T> struct is_vector : std::false_type {};
template <typename T, typename Allocator>
struct is_vector<std::vector<T, Allocator>> : std::true_type {};
template <typename T> inline constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
inline void printVector(const std::vector<T> &vec,
                        const bool addNewLine = true) {
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    if (i > 0)
      std::cout << ", ";
    if constexpr (is_vector_v<T>)
      printVector(vec[i], false);
    else if constexpr (is_pair_v<T>)
      printPair(vec[i], false);
    else if constexpr (is_optional_v<T>)
      if (vec[i].has_value())
        std::cout << *vec[i];
      else
        std::cout << "null";
    else
      std::cout << vec[i];
  }
  std::cout << "]";
  if (addNewLine)
    std::cout << std::endl;
}

template <typename T1, typename T2>
inline void printPair(const std::pair<T1, T2> &p,
                      const bool addNewLine = true) {
  printVector(std::vector{p.first, p.second}, addNewLine);
}

template <typename K, typename V>
inline void printMap(const std::unordered_map<K, V> &map) {
  std::cout << "{";
  int i = 0;
  for (auto &item : map) {
    if (i > 0)
      std::cout << ", ";
    std::cout << item.first << ": " << item.second;
    i++;
  }
  std::cout << "}" << std::endl;
}

template <typename Func, typename... Args>
inline auto timedCall(Func &&func, Args &&...args) {
  auto start = std::chrono::steady_clock::now();
  auto result =
      std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
  auto end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << elapsed.count() << " us" << std::endl;
  return result;
}

template <typename T1, typename T2> struct PairHash {
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    // Combine hashes (boost-style combine)
    return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
  }
};
