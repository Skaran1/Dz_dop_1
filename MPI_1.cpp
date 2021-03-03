#include <stdio.h>
#include <iostream>


int main(){
  int steps = 0;
  std::cin >> steps;
  double summ_e = 1;
  double x = 1;
  for (int i = 1; i <= steps; i++){
    std::cout << x << std::endl;
      x = x / i;
      summ_e += x;
    }
  std::cout << summ_e << std::endl;
}
