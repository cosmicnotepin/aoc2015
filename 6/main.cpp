#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <bitset>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    array<bitset<1000>, 1000> grd;
    std::regex pat {R"(\d+)"};
    std::smatch sm;
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        auto it = sregex_iterator(line.begin(), line.end(), pat);
        array<int, 4> vals;
        transform(it, sregex_iterator(), vals.begin(),
                [](auto v) {return stoi(string(v.str()));});
        auto [xm, ym, xM, yM] = vals;
        for (auto y=ym; y<=yM; ++y)
            for (auto x=xm; x<=xM; ++x)
                switch (line[6]) {
                    case 'f':
                        grd[y].reset(x);
                        break;
                    case 'n':
                        grd[y].set(x);
                        break;
                    case ' ':
                        grd[y].flip(x);
                        break;
                }
    }
    return to_string(transform_reduce(grd.begin(), grd.end(),
            0, plus{}, [](auto v) {return v.count();}));
}

string run2(string const filename)
{
    vector<vector<int>> grd(1000, vector<int>(1000));
    std::regex pat {R"(\d+)"};
    std::smatch sm;
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        auto it = sregex_iterator(line.begin(), line.end(), pat);
        array<int, 4> vals;
        transform(it, sregex_iterator(), vals.begin(),
                [](auto v) {return stoi(string(v.str()));});
        auto [xm, ym, xM, yM] = vals;
        for (auto y=ym; y<=yM; ++y)
            for (auto x=xm; x<=xM; ++x)
                switch (line[6]) {
                    case 'f':
                        grd[y][x] = max(0, grd[y][x] - 1);
                        break;
                    case 'n':
                        ++grd[y][x];
                        break;
                    case ' ':
                        grd[y][x] += 2;
                        break;
                }
    }
    return to_string(transform_reduce(grd.begin(), grd.end(),
            0LL, plus{}, [](auto v)
            {return accumulate(v.begin(), v.end(), 0LL);}));
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
