#include <iostream>
#include <cassert>
#include <chrono>

#include <string>

using namespace std;

// Count and Say
// https://leetcode.com/problems/count-and-say/

class Solution {
public:
    string countAndSay(int n) {
        if ( n <= 1 ) return "1";
        if ( n == 2 ) return "11";

        string neu;
        neu.reserve(4462);
        neu = "11";
        string* neu_ptr = &neu;
        
        string cur;
        cur.reserve(4462);
        string* cur_ptr = &cur;
        
        for(int i = 3; i <= n; ++i) {

            string* t = cur_ptr;
            cur_ptr = neu_ptr;
            neu_ptr = t;
            neu_ptr->clear();

            auto last = cur_ptr->begin();
            auto it = last + 1;
            for(; it != cur_ptr->end(); ++it) {
                if( (*(it-1)) != (*it) ) {
                    neu_ptr->push_back('0' + it - last);
                    neu_ptr->push_back((*(it-1)));
                    last = it;
                }
            }
            neu_ptr->push_back('0' + it - last);
            neu_ptr->push_back(cur_ptr->back());
        }

        return *neu_ptr;

        /*
        string cur = "11";
        for(int i = 3; i <= n; ++i) {
            string neu;

            auto last = cur.begin();
            auto it = last + 1;
            for(; it != cur.end(); ++it) {
                if( *(it-1) != *it ) {
                    neu.push_back('0' + it - last);
                    neu.push_back(*(it-1));
                    last = it;
                }
            }
            neu.push_back('0' + it - last);
            neu.push_back(cur.back());

            cur = neu;
        }

        return cur;
        */
    }
};

int main() {

    Solution s;

    assert(s.countAndSay(-1) == "1");
    assert(s.countAndSay(0) == "1");
    assert(s.countAndSay(1) == "1");
    assert(s.countAndSay(2) == "11");
    assert(s.countAndSay(3) == "21");
    assert(s.countAndSay(4) == "1211");
    assert(s.countAndSay(5) == "111221");
    assert(s.countAndSay(6) == "312211");
    assert(s.countAndSay(7) == "13112221");


    chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    s.countAndSay(30);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "elapsed time: " << elapsed_seconds.count() << endl;


    for (int i = 1; i <= 30; ++i) {
        cout << i << " " << s.countAndSay(i).size() << endl;
    }

    return 0;
}
