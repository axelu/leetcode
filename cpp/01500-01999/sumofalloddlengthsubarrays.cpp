
// 1588. Sum of All Odd Length Subarrays
// https://leetcode.com/contest/biweekly-contest-35/problems/sum-of-all-odd-length-subarrays/
// https://leetcode.com/problems/sum-of-all-odd-length-subarrays/



#include <iostream>
#include <cassert>
#include <chrono>
#include <bitset>

#include <vector>
#include <numeric>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        auto as = arr.size();
        if( as == 0 ) return 0;
        if( as == 1 ) return arr[0];

        int r = 0;

        // brute force
        int i = 1;
        int d = 1;
        while( d <= as ) {
            // cout << d << endl;
            for(auto it = arr.begin(); it + d - 1 != arr.end(); ++it) {
                // cout << *it << " ";
                r = accumulate(it, it + d, r);
            }
            // cout << endl;
            d = i * 2 + 1;
            ++i;
        }

        return r;
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<int> arr;

    arr = {1,4,2,5,3};
    cout << "{1,4,2,5,3}" << endl;
    // cout << s.sumOddLengthSubarrays(arr) << endl;
    assert(s.sumOddLengthSubarrays(arr) == 58);

    arr = {1,4,2,5,3,6};
    cout << "{1,4,2,5,3,6}" << endl;
    // cout << s.sumOddLengthSubarrays(arr) << endl;
    assert(s.sumOddLengthSubarrays(arr) == 98);

    arr = {1,2};
    cout << "{1,2}" << endl;
    // cout << s.sumOddLengthSubarrays(arr) << endl;
    assert(s.sumOddLengthSubarrays(arr) == 3);

    arr = {10,11,12};
    cout << "{10,11,12}" << endl;
    // cout << s.sumOddLengthSubarrays(arr) << endl;
    assert(s.sumOddLengthSubarrays(arr) == 66);

    arr = {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
    cout << "{1000,1000,...}" << endl;
    // cout << s.sumOddLengthSubarrays(arr) << endl;
    assert(s.sumOddLengthSubarrays(arr) == 85850000);

    return 0;
}

