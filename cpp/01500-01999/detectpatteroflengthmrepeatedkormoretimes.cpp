

// 1566. Detect Pattern of Length M Repeated K or More Times
// https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/



#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        // m = length of pattern 1 <= m <= 100
        // k = min number of repetitions of pattern 2 <= k <= 100

        size_t as = arr.size();
        if( m >= as || m * k > as ) return false;

        for(auto it = arr.begin(); it != arr.end() - (m * k) + 1; ++it) {
            cout << "it pos " << it - arr.begin() << endl;
            cout << "it val " << *it << endl;

            bool c = true;

            auto itp = it;
            for(int i = 2; i <= k; ++i) {
                itp += m;

                cout << "itp pos " << itp - arr.begin() << endl;
                cout << "itp val " << *itp << endl;

                if( *it != *itp ) {
                    c = false;
                    break;
                }
            }

            if( c && m > 1 ) {
                cout << "checking pattern" << endl;
                itp = it;
                for(int i = 2; i <= m; ++i) {
                    ++itp;
                    cout << "itp pos " << itp - arr.begin() << endl;
                    cout << "itp val " << *itp << endl;
                    for(int j = 1; j < k; ++j) {
                        auto itpp = itp + j * m;
                        cout << "itpp pos " << itpp - arr.begin() << endl;
                        cout << "itpp val " << *itpp << endl;
                        if( *itp != *itpp ) c = false;
                    }
                }
            }

            if( c ) return true;
        }

        return false;
    }
};

int main() {
    Solution s;
    vector<int> v;

    cout << "v = {1,2,4,4,4,4};" << endl;
    v = {1,2,4,4,4,4};
    assert(s.containsPattern(v, 1, 3) == true);

    cout << "v = {1,2,1,2,1,1,1,3};" << endl;
    v = {1,2,1,2,1,1,1,3};
    assert(s.containsPattern(v, 2, 2) == true);

    cout << "v = {1,2,1,2,1,3};" << endl;
    v = {1,2,1,2,1,3};
    assert(s.containsPattern(v, 2, 3) == false);

    cout << "v = {1,2,3,1,2};" << endl;
    v = {1,2,3,1,2};
    assert(s.containsPattern(v, 2, 2) == false);

    cout << "v = {2,2,2,2};" << endl;
    v = {2,2,2,2};
    assert(s.containsPattern(v, 2, 3) == false);

    cout << "v = {2,2,2,2};" << endl;
    v = {2,2,2,2};
    assert(s.containsPattern(v, 2, 2) == true);

    return 0;
}
