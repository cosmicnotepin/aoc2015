#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

unordered_map<string, string> wrs;
unordered_map<string, short unsigned int> wrs_cch;

short unsigned int dfs(string wr)
{
    static regex pat {R"(\S+)"};

    if (wrs_cch.contains(wr))
        return wrs_cch[wr];

    short unsigned int res = 0;

    auto it = sregex_iterator(wrs[wr].begin(), wrs[wr].end(), pat);
    vector<string> elms;
    for (auto i = it; i!=sregex_iterator(); ++i) {
        elms.push_back((*i).str());
    }

    if (elms.size() == 1) {
        try {
            res = stoi(elms[0]);
        } catch (invalid_argument& e) {
            res = dfs(elms[0]);
        }
    }
    if (elms.size() == 2) {
        res = ~dfs(elms[1]);
    }
    if (elms.size() == 3) {
        if (elms[1] == "AND") {
            try {
                short unsigned int lhs = stoi(elms[0]);
                res = lhs & dfs(elms[2]);
            } catch (invalid_argument& e) {
                res = dfs(elms[0]) & dfs(elms[2]);
            }
        }
        if (elms[1] == "OR")
            res = dfs(elms[0]) | dfs(elms[2]);
        if (elms[1] == "LSHIFT")
            res = dfs(elms[0]) << stoi(elms[2]);
        if (elms[1] == "RSHIFT")
            res = dfs(elms[0]) >> stoi(elms[2]);
    }

    wrs_cch[wr] = res;
    return res;
}

string run1(string const filename)
{
    wrs.clear();
    wrs_cch.clear();
    ifstream ifs {filename};
    regex pat  {R"((.+) -> (.+))"};
    std::smatch sm;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        wrs[sm[2]] = sm[1];
    }
    return to_string(dfs("a"));
}

string run2(string const filename)
{
    wrs.clear();
    wrs_cch.clear();
    ifstream ifs {filename};
    regex pat  {R"((.+) -> (.+))"};
    std::smatch sm;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        wrs[sm[2]] = sm[1];
    }
    wrs["b"] = "46065";
    return to_string(dfs("a"));
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
