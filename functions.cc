#include "functions.hpp"
std::map<std::string, std::map<int, std::string>> map;
void DealWithDataOne() {
  std::vector<std::vector<std::string>> first_step;
  // std::vector<int> numbers;
  std::ifstream ifs{"/home/vagrant/src/mp-dna-forensics-haosen-yao/tests/test.dat"};
  for (std::string line; std::getline(ifs, line); line = " ") {
    std::vector<std::string> more = utilities::GetSubstrs(line, ',');
    first_step.push_back(more);
  }
  BuildTheBasicGuideBook(first_step);
}
void BuildTheBasicGuideBook(std::vector<std::vector<std::string>> first_step) {
  for (unsigned int i = 1; i < first_step.size(); ++i) {
    for (unsigned int k = 1; k < first_step.at(i).size(); ++k) {
      std::map<int, std::string> temp;
      for (unsigned int j = 1; j < first_step.size(); ++j) {
        temp.insert(std::pair<int, std::string>{
            std::stoi(first_step.at(j).at(k)), first_step.at(j).at(0)});
      }
      map.insert(std::pair<std::string, std::map<int, std::string>>{
          first_step.at(0).at(k), temp});
    }
  }
} //lack one no match way.
std::vector<std::string> CopWithTarget(std::string a) { 
  std::vector<std::string> x;
  for (auto map_pair : map) {
    if(a.find(map_pair.first) < a.size()) {
      x.push_back(map_pair.first);
    }
  }
  return x; 
}
int CWithTarget(std::string b, std::string target, int count) {
  if (target.find(b) > target.size()) {
    return count;
  }
  unsigned int important = target.find(b);
  count = count + 1;
  target.erase(target.find(b), b.length());
  if (target.find(b) == important) {
    return CWithTarget(b, target, count);
  } else {
    if (CWithTarget(b, target, 0) > count) {
      return CWithTarget(b, target, 0);
    }
  }
  return count;
}
bool FindHelper(std::map<int, std::string> temp, int x) {
  for (auto map_pair : temp) {
    if (map_pair.first == x) {
      return true;
    }
  }
  return false;
}
std::string FinalOperate(std::string abc, int x) {
  for (auto map_pair : map) {
    if (map_pair.first == abc && FindHelper(map.at(abc), x)) {
      return map.at(abc).at(x);
    }
  }
  return "No match";
}
std::string Result(std::string target) {
  DealWithDataOne();
  //std::cout << map.at("AGATG").at(5) << std::endl;
  std::vector<std::string> aim = CopWithTarget(target);
  std::string ans;
  for (unsigned int i = 0; i < aim.size(); ++i) {
    int temp = CWithTarget(aim.at(i), target, 0);
    ans = FinalOperate(aim.at(i), temp);
/*     std::cout << aim.at(i) << std::endl;
    std::cout << temp << std::endl;
    std::cout << target << std::endl */;
  }
  //std::cout << ans << std::endl;
  return ans;
}