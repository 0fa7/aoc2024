#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void helper(std::vector<int> bu, std::vector<int> slate,
            std::unordered_set<int> &v, std::vector<int> &ans, int ix,
            std::unordered_map<int, std::unordered_set<int>> &paths) {
  
  if (v.find(ix) != v.end()) {
    return;
  }
  //std::cout << bu[ix] << " ";

  

  v.insert(ix);
  slate.push_back(bu[ix]);

  if (v.size() == bu.size()) {
    //std::cout << "hello" << std::endl;
    ans = slate;
    return;
  }

  for (int run = 0; run < bu.size(); run++) {
    if (paths[bu[ix]].find(bu[run]) != paths[bu[ix]].end() &&
        v.find(run) == v.end()) {
      helper(bu, slate, v, ans, run, paths);
    }
  }

  v.erase(ix);
  slate.pop_back();

  //std::cout << "---" << std::endl;
}

int main() {
  std::ifstream paths_input("../05_paths.txt");
  std::ifstream updates_input("../05_updates.txt");

  std::string line;

  std::unordered_map<int, std::unordered_set<int>> paths;
  std::vector<std::vector<int>> updates;

  unsigned long long sum = 0;
  int lines = 0;

  while (getline(paths_input, line)) {
    std::stringstream ss(line);

    std::string s;
    std::string d;

    std::getline(ss, s, '|');
    std::getline(ss, d, '|');

    paths[std::stoi(s)].insert(std::stoi(d));

    std::cout << s << "->" << d << std::endl;
  }

  while (getline(updates_input, line)) {
    std::stringstream ss(line);

    std::string token;
    std::vector<int> update;

    while (std::getline(ss, token, ',')) {
      update.push_back(std::stoi(token));
    }

    if (!update.empty()) {
      updates.push_back(update);
    }
  }

  std::vector<std::vector<int>> bad_updates;

  for (int i = 0; i < updates.size(); i++) {
    std::vector<int> pages;
    bool is_good = true;

    for (auto j = 0; j < updates[i].size() - 1; j++) {
      pages.push_back(updates[i][j]);

      if (paths[updates[i][j]].find(updates[i][j + 1]) ==
          paths[updates[i][j]].end()) {
        is_good = false;
      }
    }

    pages.push_back(updates[i][updates[i].size() - 1]);

    if (is_good) {
      sum += pages[pages.size() / 2];
    } else {
      bad_updates.push_back(pages);
    }
  }

  int bad_update_sum = 0;

  /*for(auto& bad_update : bad_updates)
  {
    std::unordered_set<int> v;
    std::vector<int> slate;
    std::vector<int> ans;

    std::cout << "og: ";
    for(auto num : bad_update)
    {
      std::cout << num << " ";
    }

    std::cout << std::endl;

    for(int ix = 0; ix < bad_update.size(); ix++)
    {
      helper(v, slate, bad_update, ix, bad_update.size(), ans, paths);

      if(!ans.empty())
      {
        bad_update_sum += ans[slate.size() / 2];

      }
    }
  std::cout << "ans: ";
  for (auto num : ans) {
    std::cout << num << " ";
  }

  std::cout << std::endl;

  // dfs to find valid path;
}*/

  int slns_found = 0;

  for (auto &bu : bad_updates) {

    std::cout << "bu: ";
    for (auto num : bu) {
      std::cout << num << " ";
    }

    std::cout << std::endl;

    for (int ix = 0; ix < bu.size(); ix++) {
      std::vector<int> ans;
      std::vector<int> slate;
      std::unordered_set<int> v;

      helper(bu, slate, v, ans, ix, paths);

      if (!ans.empty()) {
        bad_update_sum += ans[ans.size() / 2];
        slns_found++;
        break;
      }
    }
  }

  std::cout << sum << std::endl;
  std::cout << bad_update_sum << std::endl;
  std::cout << ((slns_found == bad_updates.size()) ? "YES" : "HELL NO") << std::endl;

  return 1;
}