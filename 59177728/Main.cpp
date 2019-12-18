#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string Method1(const std::string &str, int val) {
  if (str == "FIRST") {
    std::array<std::string, 3> real_value = {"FIRST", "hai1", "bye1"};
    return real_value[val];
  } else if (str == "SECOND") {
    std::array<std::string, 3> real_value = {"Hello1", "SECOND", "bye1"};
    return real_value[val];
  } else if (str == "THIRD") {
    std::array<std::string, 3> real_value = {"Hello1", "hai1", "THIRD"};
    return real_value[val];
  } else if (str == "FOURTH") {
    std::array<std::string, 3> real_value = {"FOURTH", "hai1", "bye1"};
    return real_value[val];
  } else if (str == "FIFTH") {
    std::array<std::string, 3> real_value = {"Hello1", "FIFTH", "bye1"};
    return real_value[val];
  }
  return "";
}

std::string Method2(const std::string &str, int val) {
  static std::array<std::string, 3> real_value1 = {"FIRST", "hai1", "bye1"};
  static std::array<std::string, 3> real_value2 = {"Hello1", "SECOND", "bye1"};
  static std::array<std::string, 3> real_value3 = {"Hello1", "hai1", "THIRD"};
  static std::array<std::string, 3> real_value4 = {"FOURTH", "hai1", "bye1"};
  static std::array<std::string, 3> real_value5 = {"Hello1", "FIFTH", "bye1"};
  if (str == "FIRST") {
    return real_value1[val];
  } else if (str == "SECOND") {
    return real_value2[val];
  } else if (str == "THIRD") {
    return real_value3[val];
  } else if (str == "FOURTH") {
    return real_value4[val];
  } else if (str == "FIFTH") {
    return real_value5[val];
  }
  return "";
}

int GetEnumIndex(const std::string &str) {
  if (str == "FIRST") {
    return 0;
  } else if (str == "SECOND") {
    return 1;
  } else if (str == "THIRD") {
    return 2;
  } else if (str == "FOURTH") {
    return 3;
  } else if (str == "FIFTH") {
    return 4;
  }
  return -1;
}
std::string Method3(const std::string &str, int val) {
  std::vector<std::vector<std::string>> stringArray{
      {"FIRST", "hai1", "bye1"},
      {"Hello1", "SECOND", "bye1"},
      {"Hello1", "hai1", "THIRD"},
      {"FOURTH", "hai1", "bye1"},
      {"Hello1", "FIFTH", "bye1"}};
  auto index = GetEnumIndex(str);
  if (index != -1) {
    return stringArray[index][val];
  }
  return "";
}
std::string Method4(const std::string &str, int val) {
  static std::vector<std::vector<std::string>> stringArray{
      {"FIRST", "hai1", "bye1"},
      {"Hello1", "SECOND", "bye1"},
      {"Hello1", "hai1", "THIRD"},
      {"FOURTH", "hai1", "bye1"},
      {"Hello1", "FIFTH", "bye1"}};
  auto index = GetEnumIndex(str);
  if (index != -1) {
    return stringArray[index][val];
  }
  return "";
}
std::string Method5(const std::string &str, int val) {
  static std::map<std::string, std::vector<std::string>> stringMap{
      {"FIRST", {"FIRST", "hai1", "bye1"}},
      {"SECOND", {"Hello1", "SECOND", "bye1"}},
      {"THIRD", {"Hello1", "hai1", "THIRD"}},
      {"FOURTH", {"FOURTH", "hai1", "bye1"}},
      {"FIFTH", {"Hello1", "FIFTH", "bye1"}}};
  auto index = stringMap.find(str);
  if (index != stringMap.end()) {
    return index->second[val];
  }
  return "";
}
std::string Method6(const std::string &str, int val) {
  static std::array<std::string, 5> NUMBERS{"FIRST", "SECOND", "THIRD",
                                            "FOURTH", "FIFTH"};
  static std::array<std::vector<std::string>, 5> VALUES{
      std::vector<std::string>{"FIRST", "hai1", "bye1"},
      std::vector<std::string>{"Hello1", "SECOND", "bye1"},
      std::vector<std::string>{"Hello1", "hai1", "THIRD"},
      std::vector<std::string>{"FOURTH", "hai1", "bye1"},
      std::vector<std::string>{"Hello1", "FIFTH", "bye1"}};
  for (int i = 0; i < NUMBERS.size(); ++i) {
    if (NUMBERS[i] == str) {
      return VALUES[i][val];
    }
  }
  return "";
}
#include  <unordered_map>
std::string Method7(const std::string &str, int val) {
  static std::unordered_map<std::string, std::vector<std::string>> stringMap{
      {"FIRST", {"FIRST", "hai1", "bye1"}},
      {"SECOND", {"Hello1", "SECOND", "bye1"}},
      {"THIRD", {"Hello1", "hai1", "THIRD"}},
      {"FOURTH", {"FOURTH", "hai1", "bye1"}},
      {"FIFTH", {"Hello1", "FIFTH", "bye1"}}};
  auto index = stringMap.find(str);
  if (index != stringMap.end()) {
    return index->second[val];
  }
  return "";
}

using CompareMethod = std::function<std::string(const std::string &, int)>;
bool validate(CompareMethod method, const std::string &name) {
  std::map<std::string, int> testResult{
      {"FIRST", 0}, {"SECOND", 1}, {"THIRD", 2}, {"FOURTH", 0}, {"FIFTH", 1}};
  for (auto &test : testResult) {
    if (method(test.first, test.second) != test.first) {
      std::cout << name << " failed for " << test.first << ":" << test.second
                << std::endl;
      return false;
    }
  }
  return true;
}

#define COUNT 1000

void benchmark(CompareMethod method, const std::string &name) {
  std::map<std::string, int> testResult{
      {"FIRST", 0}, {"SECOND", 1}, {"THIRD", 2}, {"FOURTH", 0}, {"FIFTH", 1}};
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < COUNT; ++i) {
    for (auto &test : testResult) {
      auto ret = method(test.first, test.second);
    }
  }
  auto end = std::chrono::system_clock::now();
  std::cout << name << "\t"
            << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                   .count()
            << "\n";
}
#define ADD_CASE(x)                                                            \
  case x:                                                                      \
    if (validate(Method##x, "Method" #x)) {                                    \
      benchmark(Method##x, "Method" #x);                                       \
    }                                                                          \
    break;
int main(int argc, char **argv) {
  switch (std::stoi(argv[1])) {
    ADD_CASE(1);
    ADD_CASE(2);
    ADD_CASE(3);
    ADD_CASE(4);
    ADD_CASE(5);
    ADD_CASE(6);
    ADD_CASE(7);
  }
  return 0;
}