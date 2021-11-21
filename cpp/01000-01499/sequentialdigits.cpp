
// day 19 September 2020 challenge
// 1291. Sequential Digits
// https://leetcode.com/problems/sequential-digits/


#include <iostream>
#include <cassert>

#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        // 10 <= low <= high <= 10^9
        // with that 12 is lowest sequential digits number
        // and 123456789 is highest sequential digits number

        vector<int> r;

        if( high < 12 || low > 123456789 ) return r;
        if( high == low ) {
            if ( isSequentialNumber(low) )
                r = {low};
            return r;
        } else if ( high == 12 ) {
            r = {12};
            return r;
        } else if ( low == 123456789 ) {
            r = {123456789};
            return r;
        }

        if( low < 12 ) low = 12;
        if( high > 123456789 ) high = 123456789;

        // get 1st digit as starting point
        // int s = min(getFirstDigit(low), getFirstDigit(high));
        int s = 1;

        for(int i = s; i < 9; ++i) {
            genSequentialDigits(r, i, low, high);
        }

        sort(r.begin(), r.end());

        return r;
    }
private:
    bool isSequentialNumber(int x) {
        int rem = x % 10;
        while( x > 10 ) {
            int t = rem;
            x /= 10;
            rem = x % 10;
            if ( t - 1 != rem ) return false;
        }
        return true;
    }

    int getFirstDigit(int n) {
        while( n >= 10 )
            n /= 10;
        return n;
    }

    void genSequentialDigits(vector<int>& r, int a = 1,
        int l = 12, int h = 123456789) {

        // cout << "a " << a << endl;

        int ld = a % 10;
        if( ld == 9 ) return;

        int nd = ld + 1;
        int n = stoi(to_string(a).append(to_string(nd)));

        // cout << "n " << n << endl;
        // if( l <= n && h >= n ) cout << "n " << n << endl;
        if( l <= n && h >= n ) r.push_back(n);

        genSequentialDigits(r, n, l, h);
    }
};

int main() {

    Solution s;
    int low, high;
    vector<int> r;

    low = 12;
    high = 123456789;
    r = s.sequentialDigits(low, high);
    // cout << "r " << endl;
    // for(int i : r) cout << i << " " << endl;
    // assert(s.sequentialDigits(low, high) == r);

    low = 100;
    high = 300;
    r = {123,234};
    assert(s.sequentialDigits(low, high) == r);

    low = 1000;
    high = 13000;
    r = {1234,2345,3456,4567,5678,6789,12345};
    assert(s.sequentialDigits(low, high) == r);


    low = 58;
    high = 155;
    r = {67,78,89,123};
    assert(s.sequentialDigits(low, high) == r);

    return 0;
}
