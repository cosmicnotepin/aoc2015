#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <array>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct State {
    int hp_m;
    int m_m;
    int hp_b;
    int rt[3];
};

struct Spell
{
    int cost;
    int damage;
    int healing;
    int duration;
    int mana_reg;
    int shield;
};

int d_b = 9;

unordered_map<int, string> sp_n {{0,"MM"}, {1,"DR"}, {2,"SH"}, {3, "PO"}, {4,"RE"}};

array<Spell, 5> spells {
    Spell {53, 4,0,0,0,  0}, 
          {73, 2,2,0,0,  0}, 
          {113,0,0,6,0,  7},
          {173,3,0,6,0,  0},
          {229,0,0,5,101,0}};

void effect(State & s)
{
    for (size_t i=0; i<3; ++i) {
        if (s.rt[i] == 0)
            continue;
        --s.rt[i];
        //cout<<"effect: "<<sp_n[i+2]<<'\n';
        s.hp_b -= spells[i+2].damage;
        s.m_m += spells[i+2].mana_reg;
    }
}

void cast(State & s, int spell)
{
    s.m_m -= spells[spell].cost;
    //cout<<"cast: "<<sp_n[spell]<<'\n';
    if (spell > 1) {// effect
        s.rt[spell-2] = spells[spell].duration;
        return;
    }
    s.hp_m += spells[spell].healing;
    s.hp_b -= spells[spell].damage;
}

int least_to_win = 99999;

int dfs(State s, int m_so_far)
{
    int mn = 99999;

    if (--s.hp_m <=0)
        return 99999;

    effect(s);

    for (size_t i=0; i<spells.size(); ++i) {
        if (s.m_m < spells[i].cost || (i>1 && s.rt[i-2] > 0) ||
                m_so_far + spells[i].cost >= least_to_win)
            continue;
        State ls = s;
        cast(ls, i);
        //bossround
        bool shield = ls.rt[0] > 0;
        effect(ls);
        if (ls.hp_b <= 0) {
            least_to_win = min(least_to_win, m_so_far + spells[i].cost);
            mn = min(mn, spells[i].cost);
            continue;
        }
        ls.hp_m -= max(1, d_b - (shield ? 7 : 0));
        if (ls.hp_m <= 0)
            continue;
        mn = min(mn, spells[i].cost + dfs(ls, m_so_far + spells[i].cost));
    }
    return mn;
}

string run1(string const filename)
{
    State start {50, 500, 51, {0,0,0}};
    return to_string(dfs(start, 0));
}

string run2(string const filename)
{
    return to_string(0);
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
