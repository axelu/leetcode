#include <iostream>
#include <cassert>

#include <vector>
#include <unordered_map>

using namespace std;

// day 11 of the August 2020 challenge
// H-Index https://en.wikipedia.org/wiki/H-index
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3420/

class Solution {
public:
    int hIndex(vector<int>& citations) {

        if ( citations.empty() ) return 0;
        if ( citations.size() == 1 ) {
            if ( citations[0]  > 0 ) {
                return 1;
            } else {
                return 0;
            }
        }

        int hidx = 0;

        unordered_map<int, int> m;
        for (auto it = citations.begin(); it != citations.end(); ++it) {
            // debug
            // cout << *it << endl;
           
            // if ( *it == 0 ) {
            //        auto p = m.insert({0, 1});
            //        if ( !p.second ) {
            //            p.first->second++;
            //        }
            //} else {
                for (int i = *it; i >= 1; --i) {
                    auto p = m.insert({i, 1});
                    if ( !p.second ) {
                        p.first->second++;
                    }
                    if ( p.first->second >= i && i > hidx) hidx = i;
                }
            // }
        }
/*
        if ( m.size() == 1 ) {
            return 0;
        } else {
            // adjust hidx down if needed
            // debug
            cout << "h index before adjustment " << hidx << endl;
            for (auto kv : m ) {
                cout << kv.first << " " << kv.second << endl;
            }



        }

*/
        return hidx;
    }
};

int main() {

    Solution s;
    
    vector<int> v1 = {3,0,6,1,5};
    assert(s.hIndex(v1) == 3);

    vector<int> v2 = {0};
    assert(s.hIndex(v2) == 0);

    vector<int> v3 = {10};
    assert(s.hIndex(v3) == 1);

    vector<int> v4 = {0,0,0,0,0};
    assert(s.hIndex(v4) == 0);


    return 0;
}
