#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

int main()
{
  // part 1
  std::vector<int> c0(1000, 0);
  std::vector<int> c1(1000, 0);
  std::unordered_map<int, int> r_counts;

  std::string line;

  std::ifstream input("../01_input.txt");

  int i = 0;

  while(getline(input, line))
  {
    std::string tok;
    std::stringstream ss(line);

    ss >> c0[i];
    ss >> c1[i];
    r_counts[c1[i]]++;

    //std::cout << c0[i] << " " << c1[i] << std::endl;
    i++;
  }

  std::sort(c0.begin(), c0.end());
  std::sort(c1.begin(), c1.end());

  int64_t sum = 0;

  for(int i = 0; i < 1000; i++)
  {
    sum += abs(c0[i] - c1[i]);
  }

  std::cout << sum << std::endl;

  // part 2
  sum = 0;

  for(int i = 0; i < 1000; i++)
  {
    sum += (c0[i] * r_counts[c0[i]]); 
  }

  std::cout << sum << std::endl;
}