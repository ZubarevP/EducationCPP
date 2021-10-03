#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void PrintVectorPart(const std::vector<int>& numbers) {
    auto Res = find_if(numbers.begin(), numbers.end(), [] (const int& ar) {return ar < 0;});
    for (auto IT = Res; IT != numbers.begin();  ) {
      cout << *(--IT) << " ";
    }
}
/*
int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  std::cout << std::endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  std::cout << std::endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  std::cout << std::endl;
  return 0;
  
}*/
