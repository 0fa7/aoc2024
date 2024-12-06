#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
  std::ifstream input("../03_input.txt");
  std::string line;
  std::regex mul_pattern(R"(mul\(\d{1,3}\,\d{1,3}\))");

  unsigned long long sum = 0;

  std::string instructions;

  while (getline(input, line)) {

    std::stringstream ss(line);

    instructions.append(line);
  }

  bool search_for_dont = true;
  std::string do_str = "do()";
  std::string dont_str = "don't()";
  size_t l = 0;
  size_t r = 0;

  while (l < instructions.size()) {
    if (search_for_dont) {
      r = instructions.find(dont_str, l);
      std::cout << instructions.substr(l, r - l) << std::endl;
      std::string substr = instructions.substr(l, r - l);

      auto words_begin = std::sregex_iterator(substr.begin(),
                                              substr.end(), mul_pattern);
      auto words_end = std::sregex_iterator();

      // std::cout << "Found " << std::distance(words_begin, words_end) << "
      // words\n";

      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        // std::cout << "  " << match_str << '\n';

        std::regex mul_pattern(R"(\d{1,3})");

        auto nums_begin = std::sregex_iterator(match_str.begin(),
                                               match_str.end(), mul_pattern);
        auto nums_end = std::sregex_iterator();

        std::sregex_iterator j = nums_begin;
        std::smatch num = *j;
        std::string num_str = num.str();

        int a = std::stoi(num_str);
        ++j;
        num = *j;
        num_str = num.str();
        int b = std::stoi(num_str);
        // std::cout << a << " " << b << std::endl;
        sum += a * b;
      }
    } else {
      r = instructions.find(do_str, l);
    }

    search_for_dont = !search_for_dont;

    l = r;
  }

  std::cout << sum;
}