#include <iostream>
#include <cassert>

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// day 18 August 2020 challenge
// 967. Numbers With Same Consecutive Differences
// https://leetcode.com/problems/numbers-with-same-consecutive-differences/
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/551/week-3-august-15th-august-21st/3428/

class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        // 1 <= N <= 9 length of integers to return
        // 0 <= K <= 9 absolute difference between every two consecutive digits

        if ( N == 1 ) return {0,1,2,3,4,5,6,7,8,9};

        /*if ( K == 0 ) {
            int i = 1; // starting value
            for(int m = N-1; m >= 1; --m) i += pow(10,m);
            vector<int> v(9);
            ::generate(v.begin(), v.end(), [n = 0, i] () mutable { 
                n += i;
                return n; 
            });
            return v;
        }*/

        vector<int> r;    // result vector
        vector<int> v(N); // working vector
        for(int i = 1; i <=9; i++) {
            *(v.begin()) = i;
            generate(r,v,v.begin()+1,K);
        }
    
        return r;
    }
private:
    void generate(vector<int>& r, vector<int>& v, vector<int>::iterator itb, int const & K) {
        if( itb == v.end() ) {
            int e = 0;
            int n = 0;
            for(auto it = v.rbegin(); it != v.rend(); ++it) {
                n += *it * pow(10,e);
                ++e;
            }
            r.push_back(n);
            return;
        }

        int i = *(itb-1) + K;
        if ( i < 10 ) {
            *itb = i;
            generate(r,v,itb+1,K);
        }
        
        if ( K > 0 ) {
            i = *(itb-1) - K;
            if ( i > -1 ) {
                *itb = i;
                generate(r,v,itb+1,K);
            }
        }
    }
};

int main() {

    Solution s;

    vector<int> v;

    // N = 1
    v = {0,1,2,3,4,5,6,7,8,9};
    assert(s.numsSameConsecDiff(1,0) == v);
    assert(s.numsSameConsecDiff(1,1) == v);
    assert(s.numsSameConsecDiff(1,2) == v);
    assert(s.numsSameConsecDiff(1,3) == v);
    assert(s.numsSameConsecDiff(1,4) == v);
    assert(s.numsSameConsecDiff(1,5) == v);
    assert(s.numsSameConsecDiff(1,6) == v);
    assert(s.numsSameConsecDiff(1,7) == v);
    assert(s.numsSameConsecDiff(1,8) == v);
    assert(s.numsSameConsecDiff(1,9) == v);

    // K = 0
    v = {11,22,33,44,55,66,77,88,99};
    assert(s.numsSameConsecDiff(2,0) == v);
    v = {111,222,333,444,555,666,777,888,999};
    assert(s.numsSameConsecDiff(3,0) == v);
    // and so on
    v = {111111111,222222222,333333333,444444444,555555555,666666666,777777777,888888888,999999999};
    assert(s.numsSameConsecDiff(9,0) == v);

    
    v = {181,292,707,818,929};
    assert(s.numsSameConsecDiff(3,7) == v);

    // v = {10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98};
    // assert(s.numsSameConsecDiff(2,1) == v);




    // v = s.numsSameConsecDiff(9,0);
    v = s.numsSameConsecDiff(2,1);
    for (auto iv: v) {
        std::cout << iv << ",";
    }
    cout << endl;

    v = s.numsSameConsecDiff(9,0);
    for (auto iv: v) {
        std::cout << iv << ",";
    }
    cout << endl;



    // N = 9 and K = 9
    v = s.numsSameConsecDiff(9,9);
    for (auto iv: v) {
        std::cout << iv << ",";
    }
    cout << endl;


    return 0;
}
