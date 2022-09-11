#include <vector>
#include <algorithm>
#include <stdio.h>
#include <tuple>
#include <string>
#include <iostream> 
#include <atomic> 
#include <assert.h>
//c++ 17
//在if或switch条件中声明临时变量
void print_temp_obj()
{
    std::vector<int> vc = {1,2,2};
    if(const std::vector<int>::iterator itr = std::find(vc.begin(), vc.end(), 1);
    itr != vc.end())
    {
        puts("find success");
    }
}

//c++ 11 
//对象初始化列表
class Data
{
public:
    std::vector<int> vc;
    Data(std::initializer_list<int> list)
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            vc.push_back(*it);
        }
    }
    void print()
    {
        for(auto it:vc)
        {
            printf("data = %d\n", it);
        }
    }
};

//C++17
//C++11 新增了 std::tuple 容器用于构造一个元组，进而囊括多个返回值。
//但缺陷是，C++11/14 并没有提供一种简单的方法直接从元组中拿到并定义元组中的元素，
//尽管我们可以使用 std::tie 对元组进行拆包，但我们依然必须非常清楚这个元组包含多少个对象，
//各个对象是什么类型，非常麻烦。
//C++17 完善了这一设定，给出的结构化绑定可以让我们写出这样的代码

std::tuple<int, double, std::string> f()
{
    return std::make_tuple(1,2.3, "str");
}
void print_tuple()
{
    auto [x, y, z] = f();
    std::cout<<"x = "<< x <<"y = "<< y << "z = "<< z <<std::endl;
}

//atomic 例子
void atomic_sample()
{
    std::atomic<int> a(10);    //使用有参数构造函数
    assert(a == 10);           //隐式类型转换

    std::atomic<long> la;      //使用无参数构造函数
    std::cout<<"la = "<<la<<std::endl;

    std::cout<<"a.load() = "<<a.load()<<std::endl;   //显示调用load()

    la.store(20);                                    //显示调用store()
    std::cout<<"la stored = "<<la.load()<<std::endl;   

    assert(a.exchange(30) == 10);  //存值的同时返回原值
    assert(a == 30);               //隐式类型转换

    std::atomic<int> i = 100;
    int v = 100;
    if(i.compare_exchange_weak(v, 200))
    {
        assert(i == 200 && v == 100);
    }
    

} 

int main()
{
   // Data da = {1,2,3,4};
   // da.print();
    atomic_sample();
  //  print_tuple();
}