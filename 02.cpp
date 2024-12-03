#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> dampen_sort(const std::vector<int> &vals);
bool dampen_diff(const std::vector<int> &vals);
bool check_diffs(const std::vector<int> &vals);

int main() {
  // part 1
  std::vector<std::vector<int>> sorted_rows;
  std::vector<std::vector<int>> dampened_rows;
  std::string line;

  std::ifstream input("../02_input.txt");

  int i = 0;

  while (getline(input, line)) {
    std::string tok;
    std::stringstream ss(line);
    std::vector<int> row;

    while (ss.good()) {
      int val;
      ss >> val;
      row.push_back(val);
    }

    if (std::is_sorted(row.begin(), row.end()) ||
        std::is_sorted(row.rbegin(), row.rend())) {
      sorted_rows.push_back(row);
    } else {
      auto vec = dampen_sort(row);

      if (vec.size() != 0) {
        dampened_rows.push_back(vec);
      }
    }
  }

  int good_diffs = sorted_rows.size() + dampened_rows.size();

  for (const auto &row : sorted_rows) {
    if(!check_diffs(row) && !dampen_diff(row))
    {
      good_diffs--;
    }
  }

  std::cout << good_diffs << std::endl;
}

bool check_diffs(const std::vector<int> &vals)
{
  for(int i = 0; i < vals.size() - 1; i++)
  {
    int diff = std::abs(vals[i] - vals[i + 1]);
    if(diff > 3 || diff < 1)
    {
      return false;
    }
  }

  return true;
}

bool dampen_diff(const std::vector<int> &vals)
{
  for (int i = 0; i < vals.size(); i++) {
    std::vector<int> new_vec(vals);
  
    new_vec.erase(new_vec.begin() + i);

    if(check_diffs(new_vec))
    {
      return true;
    }
  }

  return false;
}

std::vector<int> dampen_sort(const std::vector<int> &vals) {
  
  for (int i = 0; i < vals.size(); i++) {
    std::vector<int> new_vec(vals);

    new_vec.erase(new_vec.begin() + i);

    if (std::is_sorted(new_vec.begin(), new_vec.end()) ||
        std::is_sorted(new_vec.rbegin(), new_vec.rend())) {
    
        if(check_diffs(new_vec))
        {
          return new_vec;
        }
    }
  }

  return {};
}