#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int checker(std::vector<std::string>& mat, int r, int c);

int main()
{
  std::ifstream input("../04_input.txt");
  std::string line;

  unsigned long long sum = 0;

  std::vector<std::string> mat;
  int lines = 0;

  while (getline(input, line)) {

    std::stringstream ss(line);
    mat.push_back(line);
    lines++;
  }

  for(int r = 1; r < mat.size() - 1; r++)
  {
    for(int c = 1; c < mat[0].size() - 1; c++)
    {
      sum += checker(mat, r, c);
      
    }
  }

  std::cout << sum << std::endl;
  std::cout << lines << std::endl;
  return 1;
}

int checker(std::vector<std::string>& mat, int r, int c)
{
  if(mat[r][c] != 'A')
  {
    return 0;
  }

  int res = 0;

  // M M
  //  A
  // S S
  if(mat[r - 1][ c - 1] == 'M' && mat[r - 1][c + 1] == 'M' && 
  mat[r + 1][ c - 1] == 'S' && mat[r + 1][c + 1] == 'S')
  {
    res++;
  }

  // M S
  //  A
  // M S
  if(mat[r - 1][ c - 1] == 'M' && mat[r - 1][c + 1] == 'S' && 
    mat[r + 1][ c - 1] == 'M' && mat[r + 1][c + 1] == 'S')
  {
    res++;
  }

  // S S
  //  A
  // M M
  if(mat[r - 1][ c - 1] == 'S' && mat[r - 1][c + 1] == 'S' && 
    mat[r + 1][ c - 1] == 'M' && mat[r + 1][c + 1] == 'M')
  {
    res++;
  }

  // S M
  //  A
  // M M
  if(mat[r - 1][ c - 1] == 'S' && mat[r - 1][c + 1] == 'M' && 
    mat[r + 1][ c - 1] == 'S' && mat[r + 1][c + 1] == 'M')
  {
    res++;
  }

  return res;
}