#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// day 12 of the August 2020 challenge
// 119. Pascal's Triangle II
// https://leetcode.com/problems/pascals-triangle-ii
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3421/

class Solution {
public:
    vector<int> getRow(int rowIndex) {

        if ( rowIndex <= 0 || rowIndex > 33 ) return {1};

        vector<int> r;
        r.insert(r.begin(), rowIndex + 1, 1);
        if ( rowIndex >= 2 ) *(r.begin() + 1) = 2;

        for (int i = 3; i <= rowIndex; i++) {
            
            int v = i - 1;
            *(r.begin()+1) = i;

            auto itmax = r.begin() + ( (i + 1) / 2 + (i + 1) % 2 );
            for (auto it = r.begin() + 2; it != itmax; ++it) {
                int tmp = *it;
                *it += v;
                v = tmp;
            }
            if ( i % 2 == 1 ) *itmax = *(itmax - 1);
        }

        auto itf = r.begin() + 1;
        auto itr = r.rbegin() + 1;
        while ( itf < itr.base() ) {
            *itr = *itf;
            itf++; itr++;
        }

        // debug
        // for (auto it = r.begin(); it != r.end(); ++it) {
        //     cout << *it << " ";
        // }
        // cout << endl;
            
        return r;
    }
};

int main() {

    Solution s;

    cout << "row  0" << endl;
    vector<int> r1 = {1};
    s.getRow(0);
    // assert(s.getRow(0) == r1);

    cout << "row  1" << endl;
    vector<int> r2 = {1,1};
    s.getRow(1);
    // assert(s.getRow(1) == r2);

    cout << "row  2" << endl;
    vector<int> r3 = {1,2,1};
    s.getRow(2);
    // assert(s.getRow(2) == r3);

    cout << "row  3" << endl;
    vector<int> r4 = {1,3,3,1};
    s.getRow(3);
    // assert(s.getRow(3) == r4);

    cout << "row  4" << endl;
    vector<int> r5 = {1,4,6,4,1};
    s.getRow(4);
    // assert(s.getRow(4) == r5);

    cout << "row  5" << endl;
    s.getRow(5);

    cout << "row 6" << endl;
    s.getRow(6);

    
    for (int i = 0; i <=33; i++) {

        vector<int> v = s.getRow(i);
        for (auto it = v.begin(); it != v.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;
}
