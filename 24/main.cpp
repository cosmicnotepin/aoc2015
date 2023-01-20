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
                if (R >N)
                    cerr<<"want me to choose "<<R<<" from "<<N<<", nope :)\n";
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

long long unsigned int product(const vector<int> & v)
{
    return accumulate(v.begin(), v.end(), 1LLU, multiplies {});
}

int sum(const vector<int> & v)
{
    return accumulate(v.begin(), v.end(), 0);
}

string run1(string const filename)
{
    vector<int> ps;
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        ps.push_back(stoi(line));
    }
    int total=sum(ps);
    int third = total/3;
    size_t max_front_size = ps.size();
    vector<int> bsf(ps);
    long long unsigned int product_bsf = product(bsf);

    for (size_t nf=1; nf<=max_front_size; ++nf) {
        for (auto fp : Combinations(ps.begin(), ps.end(), nf)) {
            int front_w = sum(fp);
            long long unsigned int fp_product = product(fp); 
            if (front_w != third || fp_product >= product_bsf)
                continue;
            vector<int> back_ps;
            for (auto p : ps)
                if (find(fp.begin(), fp.end(), p) == fp.end())
                    back_ps.push_back(p);
            for (size_t nl=1; nl<=ps.size()-nf; ++nl) {
                for (auto lp : Combinations(back_ps.begin(), back_ps.end(), nl)) {
                    if (sum(lp) != third)
                        continue;
                    max_front_size = fp.size();
                    product_bsf = fp_product;
                    bsf = fp;
                }
            }
        }
    }
    return to_string(product_bsf);
}

bool divide_evenly(vector<int> ps, int divisions, int size)
{
    for (size_t nl=1; nl<=ps.size(); ++nl) {
        for (auto lp : Combinations(ps.begin(), ps.end(), nl)) {
            if (sum(lp) != size)
                continue;
            if (divisions == 2)
                return true;

            vector<int> rest_ps;
            for (auto p : ps)
                if (find(lp.begin(), lp.end(), p) == lp.end())
                    rest_ps.push_back(p);
            if (divide_evenly(rest_ps, divisions-1, size))
                return true;
        }
    }
    return false;
}

string run2(string const filename)
{
    vector<int> ps;
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
        ps.push_back(stoi(line));
    }
    int total=sum(ps);
    int fourth = total/4;
    size_t max_front_size = ps.size();
    vector<int> bsf(ps);
    long long unsigned int product_bsf = product(bsf);

    for (size_t nf=1; nf<=max_front_size; ++nf) {
        for (auto fp : Combinations(ps.begin(), ps.end(), nf)) {
            int front_w = sum(fp);
            long long unsigned int fp_product = product(fp); 
            if (front_w != fourth || fp_product >= product_bsf)
                continue;

            vector<int> back_ps;
            for (auto p : ps)
                if (find(fp.begin(), fp.end(), p) == fp.end())
                    back_ps.push_back(p);
            for (size_t nl=1; nl<=ps.size()-nf; ++nl) {
                for (auto lp : Combinations(back_ps.begin(), back_ps.end(), nl)) {
                    if (sum(lp) != fourth)
                        continue;

                    vector<int> back_back_ps;
                    for (auto p : back_ps)
                        if (find(lp.begin(), lp.end(), p) == lp.end())
                            back_back_ps.push_back(p);
                    for (size_t nr=1; nr<=ps.size()-nf-nl; ++nr) {
                        for (auto rp : Combinations(back_back_ps.begin(), back_back_ps.end(), nr)) {
                            if (sum(rp) != fourth)
                                continue;
                            max_front_size = fp.size();
                            product_bsf = fp_product;
                            bsf = fp;
                        }
                    }
                }
            }
        }
    }
    return to_string(product_bsf);
}

int main(int argc, char** argv)
{
    for (auto [p,fun] : (pair<string, decltype(&run1)>[]) {{"p1: ", run1}, {"p2: ", run2}}) {
        cout<<p<<'\n';
        for (auto inp : {"input"}) {
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
