#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


string run1(string line)
{
    string res;
    for (int i=0; i<40; ++i) {
        char last_c = line[0];
        int count = 0;
        for (char c : line) {
            if (c != last_c) {
                res.append(to_string(count) + last_c);
                count = 0;
                last_c = c;
            }
            ++count;
        }
        res.append(to_string(count) + last_c);
        line = res;
        res.clear();
    }
    return to_string(line.size());
}


string run2(string line)
{
    string res;
    for (int i=0; i<50; ++i) {
        char last_c = line[0];
        int count = 0;
        for (char c : line) {
            if (c != last_c) {
                //res.append(to_string(count) + last_c);
                //below is 5 times faster!
                res.push_back('0'+count);
                res.push_back(last_c);
                count = 0;
                last_c = c;
            }
            ++count;
        }
        //res.append(to_string(count) + last_c);
        //below is 5 times faster!
        res.push_back('0'+count);
        res.push_back(last_c);
        line = move(res);
        res.clear();
    }
    return to_string(line.size());
}

int main(int argc, char** argv)
{
    for (auto [p,fun] : (pair<string, decltype(&run1)>[]) {{"p1: ", run1}, {"p2: ", run2}}) {
        cout<<p<<'\n';
        for (auto inp : {"111", "1113222113"}) {
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
