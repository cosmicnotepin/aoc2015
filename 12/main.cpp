#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <numeric>

#include <boost/json/src.hpp>

using namespace std;
using namespace boost;
using sri = sregex_iterator;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    static regex pat {R"(-?\d+)"};
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        auto res =  accumulate(it, {}, 0, [] (int val, auto & m) {
                return val + stoi(m.str());
                });
        return to_string(res);

    }
    return to_string(0);
}


int dfs(json::array v);
int dfs(json::object v);

int dfs(json::object v)
{
    int res = 0;
    for (auto e : v) {
        if (e.key() == "red")
            return 0;
        else if (e.value().is_string() && e.value().as_string() == "red")
            return 0;
        else if (e.value().is_array())
            res += dfs(e.value().as_array());
        else if (e.value().is_object())
            res += dfs(e.value().as_object());
        else if (e.value().is_int64())
            res += e.value().as_int64();
    }
    return res;
}

int dfs(json::array v)
{
    int res = 0;
    for (auto e : v) {
        if (e.is_array())
            res += dfs(e.as_array());
        else if (e.is_object())
            res += dfs(e.as_object());
        else if (e.is_int64())
            res += e.as_int64();
    }
    return res;
}


string run2(string const filename)
{
    ifstream ifs {filename};
    auto jv = json::parse(ifs);
    
    return to_string(dfs(jv.as_object()));
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
