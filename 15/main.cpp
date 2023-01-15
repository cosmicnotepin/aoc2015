#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <numeric>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void displ(auto itrbl) {
    for (auto val : itrbl)
        cout<<val<<", ";
    cout<<'\n';
}

void displl(auto itrbl) {
    for (auto val : itrbl)
        displ(val);
    cout<<'\n';
}

using uint = unsigned int;

template<typename InputIt, typename T=InputIt::value_type>
class Combinations_with_replacement {
    public:
    // member typedefs provided through inheriting from std::iterator
        class Itr: public iterator<
                        input_iterator_tag,   // iterator_category
                        vector<T>,             // value_type
                        int,                      // difference_type
                        const vector<T>*,      // pointer
                        vector<T> &>            // reference
        {
            InputIt begin;
            InputIt end;
            int R;
            bool done;
            int N;
            vector<int> inds;
            vector<T> cur;
        public:
            explicit Itr(InputIt begin, InputIt end, int R, bool done) :
                     begin{begin},
                     end{end},
                     R{R},
                     done{done},
                     N{int(distance(begin, end))},
                     inds(R, done ? distance(begin, end) - 1 : 0),
                     cur(R, *begin)
                     {}

            Itr& operator++()
            { 
                int i = inds.size() - 1;
                for(; i>=0; --i)
                    if (inds[i] != N - 1)
                        break;
                if (i == -1) {
                    done = true;
                    return *this;
                }

                int v = inds[i] + 1;
                for (size_t j=i; j<inds.size(); ++j)
                    inds[j] = v;

                for (size_t i = 0; i<inds.size(); ++i)
                    cur[i] = *(begin+inds[i]);

                return *this;
            }

            Itr operator++(int)
            {
                Itr retval = *this; ++(*this);
                return retval;
            }

            bool operator==(Itr other) const
            {
                return inds == other.inds && done == other.done;
            }

            bool operator!=(Itr other) const {return !(*this == other);}

            const vector<T> & operator*() const 
            {
                return cur;
            }
        };
        Combinations_with_replacement(InputIt begin, InputIt end, int R) : cbegin(begin), cend(end), cR(R) {}

        Itr begin() {return Itr(cbegin, cend, cR, false);}
        Itr end() {return Itr(cbegin, cend, cR, true);}
        InputIt cbegin;
        InputIt cend;
        int cR;
};


template<typename A,typename B>
using cwr = Combinations_with_replacement<A,B>;
using sri = sregex_iterator;

string run1(string const filename)
{
    auto ill = vector<vector<int>> {};
    static regex pat {R"(-?\d+)"};
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        vector<int> il;
        for (;it != sri {}; ++it)
            il.push_back(stoi((*it).str()));
        ill.emplace_back(il);
    }

    int spoons = 100;
    int mx = 0;
    vector<int> N(spoons + 1);
    iota(N.begin(), N.end(), 0);
    for (auto cmbn : cwr(N.begin(), N.end(), ill.size() -1)) {
        cmbn.emplace(cmbn.begin(), 0);
        cmbn.emplace_back(spoons);
        vector<int> part(ill.size());
        transform(cmbn.begin(), cmbn.end()-1, cmbn.begin() + 1,
                part.begin(), [] (const auto & a, const auto & b) {
                return b-a;
                });
        vector<vector<int>> ill_mul_sps(ill.size());
        transform(ill.begin(), ill.end(), part.begin(), ill_mul_sps.begin(),
                [] (const auto & il, const auto & p) {
                vector<int> pil;
                for (auto i : il)
                    pil.emplace_back(p*i);
                return pil;
                });
        vector<int> props(ill[0].size());
        for (int i = 0; i<(int)ill[0].size(); ++i)
            for (int il = 0; il<(int)ill.size(); ++il)
                props.at(i) += ill_mul_sps.at(il).at(i);

        mx = max(mx, accumulate(props.begin(), props.end() - 1,
                    1, [](const auto & v1, const auto & v2) {
                    return v1 * (v2>0 ? v2 : 0);
                    }));
    }

    return to_string(mx);
}

string run2(string const filename)
{
    auto ill = vector<vector<int>> {};
    static regex pat {R"(-?\d+)"};
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        auto it = sri(line.begin(), line.end(), pat);
        vector<int> il;
        for (;it != sri {}; ++it)
            il.push_back(stoi((*it).str()));
        ill.emplace_back(il);
    }

    int spoons = 100;
    int mx = 0;
    vector<int> N(spoons + 1);
    iota(N.begin(), N.end(), 0);
    for (auto cmbn : cwr(N.begin(), N.end(), ill.size() -1)) {
        cmbn.emplace(cmbn.begin(), 0);
        cmbn.emplace_back(spoons);
        vector<int> part(ill.size());
        transform(cmbn.begin(), cmbn.end()-1, cmbn.begin() + 1,
                part.begin(), [] (const auto & a, const auto & b) {
                return b-a;
                });
        vector<vector<int>> ill_mul_sps(ill.size());
        transform(ill.begin(), ill.end(), part.begin(), ill_mul_sps.begin(),
                [] (const auto & il, const auto & p) {
                vector<int> pil;
                for (auto i : il)
                    pil.emplace_back(p*i);
                return pil;
                });
        vector<int> props(ill[0].size());
        for (int i = 0; i<(int)ill[0].size(); ++i)
            for (int il = 0; il<(int)ill.size(); ++il)
                props.at(i) += ill_mul_sps.at(il).at(i);

        if (props.at(props.size() -1) != 500)
            continue;
        mx = max(mx, accumulate(props.begin(), props.end() - 1,
                    1, [](const auto & v1, const auto & v2) {
                    return v1 * (v2>0 ? v2 : 0);
                    }));
    }

    return to_string(mx);
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
