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

template<typename InputIt, typename T=InputIt::value_type>
class Combinations {
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
                     inds(R),
                     cur(R)
            {
                if (done)
                    iota(inds.begin(), inds.end(), N-R);
                else
                    iota(inds.begin(), inds.end(), 0);
                for (size_t i = 0; i<inds.size(); ++i)
                    cur[i] = *(begin+inds[i]);
            }

            Itr& operator++()
            { 
                int i = inds.size() - 1;
                for(; i>=0; --i)
                    if (inds[i] !=  i + N - R)
                        break;
                if (i == -1) {
                    done = true;
                    return *this;
                }

                iota(inds.begin()+i, inds.end(), inds[i] + 1);

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

        Combinations(InputIt begin, InputIt end, int R) : cbegin(begin), cend(end), cR(R) {}

        Itr begin() {return Itr(cbegin, cend, cR, false);}
        Itr end() {return Itr(cbegin, cend, cR, true);}
        InputIt cbegin;
        InputIt cend;
        int cR;
};

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
                for(; i>=-1; --i)
                    if (inds[i] != N - 1)
                        break;
                if (i < 0) {
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

auto powerset(vector<int> itrbl) {
    vector<vector<int>> ps;
    for (size_t r=0; r<itrbl.size() + 1; ++r)
        for (auto cmbn : Combinations(itrbl.begin(), itrbl.end(), r))
            ps.emplace_back(cmbn);
    return ps;
}

string run1(string const filename)
{
    ifstream ifs {filename};
    vector<int> cntnr;
    for (string line; getline(ifs, line);) {
        cntnr.emplace_back(stoi(line));
    }

    int eggnog = 150;
    if (cntnr.size() == 5)
        eggnog = 25;


    auto ps = powerset(cntnr);
    int count = accumulate(ps.begin(), ps.end(), 0,
            [eggnog] (auto acc, const auto & l) 
            {
            auto sum = accumulate(l.begin(), l.end(), 0);
            return acc + (sum == eggnog ? 1 : 0);
            });
    return to_string(count);
}

string run2(string const filename)
{
    ifstream ifs {filename};
    vector<int> cntnr;
    for (string line; getline(ifs, line);) {
        cntnr.emplace_back(stoi(line));
    }

    int eggnog = 150;
    if (cntnr.size() == 5)
        eggnog = 25;


    auto ps = powerset(cntnr);
    int min_length = accumulate(ps.begin(), ps.end(), 1000UL,
            [eggnog] (auto acc, const auto & l) 
            {
            auto sum = accumulate(l.begin(), l.end(), 0L);
            return min(acc, + (sum == eggnog ? l.size() : 10000));
            });
    auto cmbns = Combinations(cntnr.begin(), cntnr.end(), min_length);
    int count = accumulate(cmbns.begin(), cmbns.end(), 0,
            [eggnog] (auto acc, const auto & l) 
            {
            auto sum = accumulate(l.begin(), l.end(), 0);
            return acc + (sum == eggnog ? 1 : 0);
            });
    return to_string(count);
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
