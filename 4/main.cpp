#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <limits>
#include "md5.h"

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        for (int i=0; i<numeric_limits<int>::max(); ++i) {
            string res = md5(line+to_string(i));
            if (res.substr(0,5) == "00000")
                return to_string(i);
        }
    }
    return to_string(0);
}

string run2(string const filename)
{
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        for (int i=0; i<numeric_limits<int>::max(); ++i) {
            string res = md5(line+to_string(i));
            if (res.substr(0,6) == "000000")
                return to_string(i);
        }
    }
    return to_string(0);
}

int main(int argc, char** argv)
{
    for (auto [p,fun] : (pair<string, decltype(&run1)>[]) {{"p1: ", run1}, {"p2: ", run2}}) {
        cout<<p<<'\n';
        for (auto inp : {"tinput", "input"}) {
            auto start = chrono::steady_clock::now();
            auto res = fun(inp);
            auto end = chrono::steady_clock::now();
            chrono::duration<double> time_s = end-start;
            cout<<inp<<": "<<res<<'\n';
            cout<<fixed;
            cout.precision(6);
            cout<<"time: "<<time_s.count()<<'\n';
        }
    }
}
