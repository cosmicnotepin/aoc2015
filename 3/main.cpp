#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <set>
#include <valarray>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct Va_comp {
    bool operator()(const valarray<int> lhs, const valarray<int> rhs) const
    {
        for (size_t i=0; i<lhs.size(); ++i) {
            if (lhs[i] == rhs[i])
                continue;
            else
                return lhs[i] < rhs[i];
        }
        return false;
    };
};

string run1(string const filename)
{
    ifstream ifs {filename};
    string line;
    getline(ifs, line);
    set<valarray<int>, Va_comp> visited;
    map<char, valarray<int>> dir2move 
    {{'v', {0, 1}}, {'<', {-1, 0}},
        {'>', {1, 0}}, {'^', {0, -1}}};
    valarray pos {0,0};
    visited.insert(pos);
    for (auto c : line) {
        visited.insert(pos += dir2move[c]);
    }
    return to_string(visited.size());
}

string run2(string const filename)
{
    ifstream ifs {filename};
    string line;
    getline(ifs, line);
    set<valarray<int>, Va_comp> visited;
    map<char, valarray<int>> dir2move 
    {{'v', {0, 1}}, {'<', {-1, 0}},
        {'>', {1, 0}}, {'^', {0, -1}}};
    valarray<int> pos[2] {{0, 0}, {0, 0}};
    visited.insert(pos[0]);
    int i = 0;
    for (auto c : line) {
        visited.insert(pos[i=(i+1)%2]  += dir2move[c]);
    }
    return to_string(visited.size());
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
