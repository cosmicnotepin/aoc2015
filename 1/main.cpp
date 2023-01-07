#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


int run1(string const filename)
{
    ifstream ifs {filename};
    string line;
    getline(ifs, line);
    using ranges::count;
    return count(line, '(') - count(line, ')');
}

int run2(string const filename)
{
    ifstream ifs {filename};
    string line;
    getline(ifs, line);
    int floor = 0;
    for (size_t i=0; i<line.size(); ++i) {
        floor += line[i] == '(' ? 1 : -1;
        if (floor < 0)
            return i+1;
    }
    abort();
}

int main(int argc, char** argv)
{
    pair<string, decltype(&run1)> parts[] {{"p1: ", run1}, {"p2: ", run2}};
    for (auto [p,fun] : parts) {
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
