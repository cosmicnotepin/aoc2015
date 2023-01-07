#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <numeric>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    std::regex pat {R"((\d+)x(\d+)x(\d+))"};
    std::smatch sm;
    ifstream ifs {filename};
    int res = 0;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        array<int, 3> s_ls;
        transform(sm.begin()+1, sm.end(), s_ls.begin(),
                [](auto v) {return stoi(v);});
        array<int, 3> side_szs {s_ls[0]*s_ls[1], s_ls[0]*s_ls[2],
            s_ls[1]*s_ls[2]};
        int all_sides = transform_reduce(side_szs.begin(), side_szs.end(),
                0, plus{}, [](auto val){return 2*val;});
        res +=  all_sides + ranges::min(side_szs);
    }
    return to_string(res);
}

string run2(string const filename)
{
    std::regex pat {R"(\d+)"};
    ifstream ifs {filename};
    int res = 0;
    for (string line; getline(ifs, line);) {
        auto it = sregex_iterator(line.begin(), line.end(), pat);
        array<int, 3> s_ls;
        transform(it, sregex_iterator(), s_ls.begin(),
                [](auto v) {return stoi(string(v.str()));});
        res += accumulate(s_ls.begin(), s_ls.end(),1, multiplies{});
        ranges::sort(s_ls);
        res += transform_reduce(s_ls.begin(), s_ls.end()-1,
                0, plus{}, [](auto v){return 2*v;});
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
