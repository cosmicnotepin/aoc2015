#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    ifstream ifs {filename};
    int res = 0;
    string vowels = "aeiou";
    string forb[4] {"ab", "cd", "pq", "xy"};
    for (string line; getline(ifs, line);) {
        int vow_cnt = 0;
        for (auto c : vowels)
            vow_cnt += ranges::count(line, c);
        if (vow_cnt < 3)
            continue;
        for (auto fb : forb)
            if (!ranges::search(line, fb).empty())
                goto nope;
        if (ranges::adjacent_find(line) != line.end())
            res += 1;
nope:   ;
    }
    return to_string(res);
}

string run2(string const filename)
{
    ifstream ifs {filename};
    int res = 0;
    for (string line; getline(ifs, line);) {
        bool a = false;
        for (size_t i=0; i<line.size()-2; ++i) {
            string rest = line.substr(i+2);
            if (!ranges::search(rest, line.substr(i,2)).empty()) {
                a = true;
                break;
            }
        }
        bool b = false;
        for (size_t i=0; i<line.size()-2; ++i) {
            if (line[i] == line[i+2]) {
                b = true;
                break;
            }
        }
        if (a && b)
            res += 1;
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
