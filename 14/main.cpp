#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


using sri = sregex_iterator;

string run1(string const filename)
{
    static regex pat {R"(\d+)"};
    ifstream ifs {filename};
    vector<vector<int>> rds;
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        vector<int> vals(3);
        transform(it, {}, vals.begin(), [](auto & v) {return stoi(v.str());});
        rds.push_back(vals);
    }

    //int time = 1000;
    int time = 2503;
    int mx = 0;
    for (const auto & rd : rds) {
        int periods = time / (rd[1] + rd[2]);
        int rest_t = time % (rd[1] + rd[2]);
        int dist = periods * rd[0] * rd[1];
        dist += min(rest_t, rd[1]) * rd[0];
        mx = max(mx, dist);
    }

    return to_string(mx);
}

string run2(string const filename)
{
    static regex pat {R"(\d+)"};
    ifstream ifs {filename};
    vector<vector<int>> rds;
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        vector<int> vals(3);
        transform(it, {}, vals.begin(), [](auto & v) {return stoi(v.str());});
        rds.push_back(vals);
    }

    //int time_f = 1000;
    int time_f = 2503;
    vector<int> points(rds.size());
    for (auto time = 1; time<=time_f; ++time) {
        vector<int> dists;
        for (const auto & rd : rds) {
            int periods = time / (rd[1] + rd[2]);
            int rest_t = time % (rd[1] + rd[2]);
            int dist = periods * rd[0] * rd[1];
            dist += min(rest_t, rd[1]) * rd[0];
            dists.push_back(dist);
        }
        auto max = ranges::max(dists);
        for (size_t i=0; i<points.size(); ++i)
            points[i] += dists[i] >= max;
    }
    return to_string(ranges::max(points));
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
