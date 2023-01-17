#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string const filename)
{
    ifstream ifs {filename};
    string start_mol;
    getline(ifs, start_mol);
    unordered_map<string, vector<string>> subst;
    regex pat {R"((.+) => (.+))"};
    smatch sm;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        subst[sm[1]].emplace_back(sm[2]);
    }

    unordered_set<string> res;
    for (size_t i=0; i<start_mol.size(); ++i)
        if (subst.contains(start_mol.substr(i,1)))
            for (auto sub : subst[start_mol.substr(i,1)]) {
                auto cpy = string(start_mol);
                cpy.replace(i,1,sub);
                res.emplace(cpy);
            }

    for (size_t i=0; i<start_mol.size() - 1; ++i)
        if (subst.contains(start_mol.substr(i,2)))
            for (auto sub : subst[start_mol.substr(i,2)]) {
                auto cpy = string(start_mol);
                cpy.replace(i,2,sub);
                res.emplace(cpy);
            }

    return to_string(res.size());
}

struct Mol {
    int substs;
    string mol;
};

int dfs(auto & subst, Mol cur, auto & visited)
{
    int mn = 10000;
    for (auto sub : subst) {
        auto it = search(cur.mol.begin(), cur.mol.end(),
                sub.first.begin(), sub.first.end());
        while (it != cur.mol.end()) {
            auto cpy = string(cur.mol);
            size_t start = distance(cur.mol.begin(), it);
            //size_t end = start + sub.first.size();
            cpy.replace(start, sub.first.size(), sub.second);
            if (cpy == "e") {
                std::cout<<"cpy : "<<cpy <<'\n';
                std::cout<<"cur.substs + 1: "<<cur.substs + 1<<'\n';
                return cur.substs + 1;
            }
            //std::cout<<"cpy : "<<cpy <<'\n';
            if (visited.contains(to_string(cur.substs+1) + cpy))
                mn = min(mn, visited[to_string(cur.substs+1) + cpy]);
            else if (sub.second != "e")
                mn = min(mn, dfs(subst, Mol(cur.substs + 1, cpy), visited));
            it = search(++it, cur.mol.end(),
                    sub.first.begin(), sub.first.end());
        }
    }
    visited[to_string(cur.substs) + cur.mol] = mn;
    return mn;
}

int check(auto & todo, auto & subst, Mol & cur, auto & visited)
{
    //std::cout<<"cur.mol: "<<cur.mol<<'\n';
    for (auto sub : subst) {
        auto it = search(cur.mol.begin(), cur.mol.end(),
                sub.first.begin(), sub.first.end());
        while (it != cur.mol.end()) {
            auto cpy = string(cur.mol);
            size_t start = distance(cur.mol.begin(), it);
            size_t end = distance(cur.mol.begin(), it+sub.first.size());
            cpy.replace(start, end, sub.second);
            if (cpy == "e")
                return cur.substs + 1;
            if (!visited.contains(cpy) && sub.second != "e") {
                visited.insert(cpy);
                todo.emplace_back(cur.substs + 1, cpy);
            }
            it = search(++it, cur.mol.end(),
                    sub.first.begin(), sub.first.end());
        }
    }
    return -1;
}

struct mol_comp {
    bool operator()(const string & lhs, const string & rhs) const
    {
        if (lhs.size() > rhs.size())
            return true;
        else if (lhs.size() < rhs.size())
            return false;
        else 
            return lhs > rhs;
    }
};

string run2(string const filename)
{
    ifstream ifs {filename};
    string start_mol;
    getline(ifs, start_mol);
    map<string, string, mol_comp> subst;
    regex pat {R"((.+) => (.+))"};
    smatch sm;
    for (string line; getline(ifs, line);) {
        regex_match(line, sm, pat);
        subst[sm[2]] = sm[1];
    }

    for (auto sub :subst)
        std::cout<<"sub : "<<sub.first <<'\n';

    deque<Mol> todo {{0,start_mol}};
    unordered_map<string, int> visited;

    //while (true) {
    //    Mol cur = move(todo.front());
    //    todo.pop_front();
    //    auto ret = check(todo, subst, cur, visited);
    //    if (ret != -1)
    //        return to_string(ret);
    //}

    return to_string(dfs(subst, Mol(0,start_mol), visited));
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
