#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <chrono>
#include <numeric>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

using sri = sregex_iterator;

string run1(string const filename)
{
    static regex red {R"(\\(\\|\"|x[0-9a-f]{2}))"};
    ifstream ifs {filename};
    int res = 0;
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), red);
        res += accumulate(it, {}, 2, [] (int val, auto & m) {
                return val + m.str().size() - 1;
                });

    }
    return to_string(res);
}

string run2(string const filename)
{
    static regex red {R"(\\|\")"};
    ifstream ifs {filename};
    int res = 0;
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), red);
        res += accumulate(it, {}, 2, [] (int val, auto & m) {
                return val + 1;
                });

    }
    return to_string(res);
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
