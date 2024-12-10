#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

enum facing{
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3
};

std::unordered_map<char, facing> face_map{
  {'^', facing::UP}, 
  {'>', facing::RIGHT},
  {'v', facing::DOWN},
  {'<', facing::LEFT}};

std::unordered_map<facing, std::string> face_str{
  {facing::UP, "UP"}, 
  {facing::RIGHT, "RIGHT"},
  {facing::DOWN, "DOWN"},
  {facing::LEFT, "LEFT"}};

facing rotate(const facing& dir)
{
  if(dir == facing::UP)
  {
    return facing::RIGHT;
  }
  else if(dir == facing::RIGHT)
  {
    return facing::DOWN;
  }
  else if(dir == facing::DOWN)
  {
    return facing::LEFT;
  }

  return facing::UP;
}

bool is_valid(const std::pair<int, int>& pos, int r_size, int c_size)
{
  if(pos.first < 0 || pos.second < 0)
  {
    return false;
  }
  else if(pos.first >= r_size || pos.second >= c_size)
  {
    return false;
  }

  return true;
}

void move(const std::vector<std::string>& env, 
  std::pair<int, int>& curr_pos,
  facing& curr_dir,
  std::set<std::pair<int, int>>& v)
{
  v.insert(curr_pos);
  std::cout << face_str[curr_dir] << std::endl;

  if(curr_dir == facing::UP)
  {
    if(curr_pos.first - 1 >= 0)
    {
      if(env[curr_pos.first - 1][curr_pos.second] == '.')
      {
        curr_pos.first--;
      }
      else {
        std::cout << "ROTATE RIGHT" << std::endl;
        curr_dir = rotate(curr_dir);
      }
    }
    else {
      curr_pos.first--;
    }
  }
  else if(curr_dir == facing::RIGHT)
  {
    if(curr_pos.second + 1 < env[0].size())
    {
      if(env[curr_pos.first][curr_pos.second + 1] == '.')
      {
        curr_pos.second++;
      }
      else {
        std::cout << "ROTATE DOWN" << std::endl;
        curr_dir = rotate(curr_dir);
      }
    }
    else {
      curr_pos.second++;
    }
  }
  else if(curr_dir == facing::DOWN)
  {
    if(curr_pos.first + 1 < env.size())
    {
      if(env[curr_pos.first + 1][curr_pos.second] == '.')
      {
        curr_pos.first++;
      }
      else {
        std::cout << "ROTATE LEFT" << std::endl;
        curr_dir = rotate(curr_dir);
      }
    }
    else {
      curr_pos.first++;
    }
  }
  else if(curr_dir == facing::LEFT)
  {
    if(curr_pos.second - 1 >= 0)
    {
      if(env[curr_pos.first][curr_pos.second - 1] == '.')
      {
        curr_pos.second--;
      }
      else {
        std::cout << "ROTATE UP" << std::endl;
        curr_dir = rotate(curr_dir);
      }
    }
    else {
      curr_pos.second--;
    }
  }
}

int main()
{
  std::set<std::pair<int, int>> v;
  std::pair<int, int> curr_pos{-1, -1};
  facing curr_dir = facing::UP;
  std::ifstream map_input("../06_input.txt");
  std::string line;
  std::vector<std::string> env;
  int curr_line = 0;

  while (getline(map_input, line)) {
    std::stringstream ss(line);
    
    for(int i = 0; i < line.size(); i++)
    {
      if(line[i] == '^' || 
        line[i] == '>' ||
        line[i] == 'v' ||
        line[i] == '<')
        {
          curr_pos = {curr_line, i};
          curr_dir = face_map[line[i]];
          line[i] = '.';
        }
    }

    env.push_back(line);
    curr_line++;
  }

  int r = env.size();
  int c = env[0].size();

  while(is_valid(curr_pos, r, c))
  {
    std::cout << curr_pos.first << " " << curr_pos.second << std::endl;

    move(env, curr_pos, curr_dir, v);
    
  }

  std::cout << v.size() << std::endl;

  return 1;
}

