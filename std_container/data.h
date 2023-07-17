#include <string>
#include <iostream>

struct Data {
    std::string s;
    Data(std::string str) : s(std::move(str))  { std::cout << " constructed\n"; }
    ~Data() {std::cout<<"destrucued\n";}
    Data(const Data& o) : s(o.s) { std::cout << " copy constructed\n"; }
    Data(Data&& o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
    Data& operator=(const Data& other) {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    Data& operator=(Data&& other) {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
    // Overload operator<< as a member function
    friend std::ostream& operator<<(std::ostream& os, const Data& data) {
        os << data.s;  // Output the 's' member of the Data struct
        return os;
    }
};