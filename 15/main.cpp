#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

using uint = unsigned int;

template< uint N, uint R>
class Combinations_with_replacement {
    public:
    // member typedefs provided through inheriting from std::iterator
        class iterator: public std::iterator<
                        std::input_iterator_tag,   // iterator_category
                        array<uint,R>,             // value_type
                        uint,                      // difference_type
                        const array<uint,R>*,      // pointer
                        array<uint,R> &>            // reference
        {
            array<uint, R> cur;
            bool done;
        public:
            explicit iterator(bool done) : done{done} {
                if (!done) {
                    cur.fill(0);
                } else {
                    cur.fill(N);
                }
            }

            iterator& operator++()
            { 
                int i = cur.size() - 1;
                for(; i>=-1; --i)
                    if (cur[i] != N)
                        break;
                if (i < 0) {
                    done = true;
                    return *this;
                }

                uint v = cur[i] + 1;
                for (size_t j=i; j<cur.size(); ++j)
                    cur[j] = v;

                return *this;
            }

            iterator operator++(int)
            {
                iterator retval = *this; ++(*this);
                return retval;
            }

            bool operator==(iterator other) const
            {
                if (cur == other.cur && done == other.done)
                    cout<<"equals!";
                return cur == other.cur && done == other.done;
            }

            bool operator!=(iterator other) const {return !(*this == other);}

            const array<uint,R> & operator*() const {return cur;}
        };

        iterator begin() {return iterator(false);}
        iterator end() {return iterator(true);}
};


string run1(string const filename)
{
    auto blah = Combinations_with_replacement<3,2> {};
    for (auto v : blah) {
        for (auto ui : v)
            cout<<ui<<",";
        cout<<'\n';
    }
    ifstream ifs {filename};
    for (string line; getline(ifs, line);) {
    }
    return to_string(0);
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
