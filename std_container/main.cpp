#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include "test_vector.h"

template <typename T> void print_heap(const T &pq) {
  T temp = pq;
  std::cout << "Priority queue" << std::endl;
  while (!temp.empty()) {
    std::cout << "heap element" << temp.top() << std::endl;
    temp.pop();
  }
}

int main() {

  test_vector();
  test_vc_mem_fuc();
  // std::vector<int> vc = {1, 3, 2, 5, 4};
  // std::priority_queue<int> pq; // default max heap
  // std::priority_queue<int, std::vector<int>, std::greater<int>>
  //     pq_min; // min heap

  // for (auto i : vc) {
  //   std::cout << "vc element = " << i << std::endl;
  //   pq.push(i);
  //   pq_min.push(i);
  // }

  // print_heap(pq);
  // print_heap(pq_min);
  return 0;
}