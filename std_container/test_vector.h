#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H
// vector 构造及基本接口使用

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <type_traits>
#include <vector>
#include "data.h"

template <typename T> void print(const T &t) {
  for (const auto var : t) {
    std::cout << "var = " << var << std::endl;
  }
}

template <typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
  s.put('[');
  char comma[3] = {'\0', ' ', '\0'};
  for (const auto &e : v) {
    s << comma << e;
    comma[0] = ',';
  }
  return s << ']';
}

// vector 构造函数 Copies Are Always Deep
static void test_vector() {

  // ctor
  // 1) 默认构造函数。构造拥有默认构造的分配器的空容器
  // 2) 构造拥有给定分配器 alloc 的空容器。没有实现sample
  std::vector<int> vc_ct0;
  std::cout<<"sizeof(vector) : "<<sizeof(std::vector<int>)<<std::endl;
  // 3) 构造拥有 count 个有值 value 的元素的容器。
  std::vector<int> vc_ct1(10, 0);
  std::cout << "vc_ct1:" << vc_ct1;
  // 4) 构造拥有个 count 默认插入的 T
  // 实例的容器,若模板参数为类类型，调用模板参数的默认构造函数 基本类型
  std::vector<int> vc_ct2(10);
  std::cout << "vc_ct2:" << vc_ct2;

  // 5) 构造拥有范围 [first, last) 内容的容器。
  std::vector<int> vc_ct3(vc_ct1.begin(), vc_ct1.end());

  // 6) 复制构造函数。构造拥有 other 内容的容器
  // 7) 构造拥有 other 内容的容器，以 alloc 为分配器。
  // 可以指定分配器，此处无sample
  std::vector<int> vc_ct4(vc_ct3);

  // 8) 移动构造函数。用移动语义构造拥有 other 内容的容器。
  // 9) 有分配器扩展的移动构造函数。以 alloc
  // 为新容器的分配器,可以指定分配器，此处无sample
  std::vector<int> vc_ct5 = std::move(vc_ct4);

  // 10) 构造拥有 initializer_list init 内容的容器。
  std::vector<int> vc_ct6{0, 1, 2};
}

// vector 成员函数
static void test_vc_mem_fuc() {

  try {
    std::vector<int> vc{0, 1, 2, 3, 4};

    //元素访问
    // at:访问指定的元素，同时进行越界检查
    std::cout << "vc.at(0):" << vc.at(0) << "\n";
    // std::cout << "out of range vc.at(5):" << vc.at(5);

    // operator[]:访问指定的元素
    std::cout << "out of range vc[5]:" << vc[5] << "\n";

    // front:访问第一个元素 back:访问最后一个元素
    std::cout << "vc.front(): " << vc.front() << "\n";
    std::cout << "vc.back() : " << vc.back() << "\n";

    // data: 返回指向内存中数组第一个元素的指针
    std::cout << "data  : " << vc.data() << "\n";
    std::cout << "&vc[0]: " << &(vc[0]) << std::endl;
    std::cout << "&vc   : " << &vc << std::endl;

  } catch (std::out_of_range const &exc) {
    std::cout << exc.what() << std::endl;
  }

  //容量成员函数
  std::vector<int> vc1(6);

  // empty: 检查容器是否为空
  std::cout << "empty()    :" << vc1.empty() << std::endl;

  // size: 返回容纳的元素数
  std::cout << "size()     :" << vc1.size() << std::endl;

  // max_size: 返回可容纳的最大元素数
  std::cout << "max_size() : " << vc1.max_size() << std::endl;

  // reserve: 预留存储空间
  vc1.reserve(10); //设置容器预留空间大小为10

  // capacity: 返回当前存储空间能够容纳的元素数
  std::cout << "capacity() : " << vc1.capacity() << std::endl;

  // shrink_to_fit: 通过释放未使用的内存减少内存的使用
  // more efficient to reserve than it will be to shrink after the fact.
  // https://stackoverflow.com/questions/23502291/is-shrink-to-fit-the-proper-way-of-reducing-the-capacity-a-stdvector-to-its
  vc1.shrink_to_fit();
  std::cout << "capacity() : " << vc1.capacity() << std::endl;

  //修改器

  // insert: 在 pos 前插入 value
  vc1.insert(vc1.cbegin(), 1);
  std::cout << vc1 << std::endl;

  // insert: 在 pos 前插入 value 的 count 个副本。
  vc1.insert(vc1.cbegin() + 1, 4, 2);
  std::cout << vc1 << std::endl;

  //insert: 在 pos 前插入来自范围 [first, last) 的元素
  std::vector<int> vc_tmp{3, 4, 5};
  vc1.insert(vc1.cend(), vc_tmp.cbegin(), vc_tmp.cend());
  std::cout << vc1 << std::endl;

  //insert: 在 pos 前插入来自 initializer_list ilist 的元素。
  vc1.insert(vc1.cbegin()+4,{6,7,8});
  std::cout<<vc1<<std::endl;

  //emplace(C++11) :原位构造元素
  std::vector<Data> vc_data;
  vc_data.reserve(10);
  vc_data.emplace(vc_data.end(), "one");

  std::cout<<"vc_data :"<<vc_data<<std::endl;
  vc_data.emplace_back("two");
  std::cout<<"vc_data :"<<vc_data<<std::endl;
  
  Data data_tmp {"three"};
  vc_data.emplace_back(std::move(data_tmp));
  std::cout<<"vc_data :"<<vc_data<<std::endl;
  //emplace_back(C++11): 在容器末尾就地构造元素
  vc_data.emplace_back("four");

  //push_back: 将元素添加到容器末尾
  Data temp_four("five");
  vc_data.push_back(temp_four);
  vc_data.push_back(std::move(Data("six")));

  //pop_back: 移除末元素
  vc_data.pop_back();

  //erase:擦除元素
  vc_data.erase(vc_data.end());
  vc_data.erase(vc_data.cbegin(), vc_data.cbegin()+2);
  std::cout<<"vc_data :"<<vc_data<<std::endl;
  vc_data.clear();
  std::cout<<"pop_back()\n";
}
#endif