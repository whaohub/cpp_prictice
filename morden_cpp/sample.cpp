#include <vector>
#include <algorithm>
#include <stdio.h>
#include <tuple>
#include <string>
#include <iostream> 
#include <atomic> 
#include <assert.h>
//c++ 17
//��if��switch������������ʱ����
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
//�����ʼ���б�
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
//C++11 ������ std::tuple �������ڹ���һ��Ԫ�飬���������������ֵ��
//��ȱ���ǣ�C++11/14 ��û���ṩһ�ּ򵥵ķ���ֱ�Ӵ�Ԫ�����õ�������Ԫ���е�Ԫ�أ�
//�������ǿ���ʹ�� std::tie ��Ԫ����в������������Ȼ����ǳ�������Ԫ��������ٸ�����
//����������ʲô���ͣ��ǳ��鷳��
//C++17 ��������һ�趨�������Ľṹ���󶨿���������д�������Ĵ���

std::tuple<int, double, std::string> f()
{
    return std::make_tuple(1,2.3, "str");
}
void print_tuple()
{
    auto [x, y, z] = f();
    std::cout<<"x = "<< x <<"y = "<< y << "z = "<< z <<std::endl;
}

//atomic ����
void atomic_sample()
{
    std::atomic<int> a(10);    //ʹ���в������캯��
    assert(a == 10);           //��ʽ����ת��

    std::atomic<long> la;      //ʹ���޲������캯��
    std::cout<<"la = "<<la<<std::endl;

    std::cout<<"a.load() = "<<a.load()<<std::endl;   //��ʾ����load()

    la.store(20);                                    //��ʾ����store()
    std::cout<<"la stored = "<<la.load()<<std::endl;   

    assert(a.exchange(30) == 10);  //��ֵ��ͬʱ����ԭֵ
    assert(a == 30);               //��ʽ����ת��

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