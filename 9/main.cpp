#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_set>
#include <unordered_map>
#include <limits>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


vector<vector<int>> vdists;

int dfs_m(int pos, int visited)
{
    int mn = 0;
    for (size_t i=0; i<vdists[0].size(); ++i) {
        int bit = 1<<i;
        if (bit & visited)
            continue;
        mn = max(mn, dfs_m(i, visited | bit) + vdists[pos][i]);
    }
    return mn;
}

int dfs(int pos, int visited)
{
    int mn = numeric_limits<int>::max();
    for (size_t i=0; i<vdists[0].size(); ++i) {
        int bit = 1<<i;
        if (bit & visited)
            continue;
        mn = min(mn, dfs(i, visited | bit) + vdists[pos][i]);
    }
    if (mn == numeric_limits<int>::max())
        return 0;
    return mn;
}

string run1(string const filename)
{
    ifstream ifs {filename};
    regex pat {R"((.+) to (.+) = (\d+))"};
    smatch sm;
    map<string, unordered_map<string, int>> dists;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        dists[sm[1]][sm[2]] = stoi(sm[3]);
        dists[sm[2]][sm[1]] = stoi(sm[3]);
    }

    vdists = vector<vector<int>> (dists.size() + 1, vector<int>(dists.size()));
    map<string, int> n2i;
    for (int i=0; auto dsts : dists)
        n2i[dsts.first] = i++;

    for (auto dsts : dists) {
        vdists[vdists.size()-1][n2i[dsts.first]] = 0;
        for (auto dst : dsts.second)
            vdists[n2i[dsts.first]][n2i[dst.first]] = dst.second;
    }
    
    int visited = 0;
    return to_string(dfs(vdists.size() -1, visited));
}

string run2(string const filename)
{
    ifstream ifs {filename};
    regex pat {R"((.+) to (.+) = (\d+))"};
    smatch sm;
    map<string, unordered_map<string, int>> dists;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        dists[sm[1]][sm[2]] = stoi(sm[3]);
        dists[sm[2]][sm[1]] = stoi(sm[3]);
    }

    vdists = vector<vector<int>> (dists.size() + 1, vector<int>(dists.size()));
    map<string, int> n2i;
    for (int i=0; auto dsts : dists)
        n2i[dsts.first] = i++;

    for (auto dsts : dists) {
        vdists[vdists.size()-1][n2i[dsts.first]] = 0;
        for (auto dst : dsts.second)
            vdists[n2i[dsts.first]][n2i[dst.first]] = dst.second;
    }
    
    int visited = 0;
    return to_string(dfs_m(vdists.size() -1, visited));
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
