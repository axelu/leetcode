
// day 30 September 2020 challenge
// First Missing Positive
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/558/week-5-september-29th-september-30th/3478/
// https://leetcode.com/problems/first-missing-positive/




#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <iterator>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int r = 1;
        if( nums.empty() ) return r;

        set<int> s;
        copy_if(nums.begin(), nums.end(), inserter(s, s.end()),[](int a){
            return a > 0;
        });
        if( s.empty() ) return r;

        auto it = s.begin();
        if( *it > 1 ) return r;
        if( s.size() == 1 ) return r + 1; // 2
        for(++it; it != s.end(); ++it) {
            auto pv = prev(it);
            if( *it - *pv > 1 ) {
                r = *pv + 1;
                break;
            }
        }
        if( r == 1 ) r = *prev(s.end()) + 1;

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
    vector<int> nums;
    int r;

    nums = {1,2,0};
    cout << "{1,2,0}" << endl;
    r = s.firstMissingPositive(nums);
    cout << "result " << r << endl;
    assert(r == 3);

    nums = {3,4,-1,1};
    cout << "{3,4,-1,1}" << endl;
    r = s.firstMissingPositive(nums);
    cout << "result " << r << endl;
    assert(r == 2);

    nums = {7,8,9,11,12};
    cout << "{7,8,9,11,12}" << endl;
    r = s.firstMissingPositive(nums);
    cout << "result " << r << endl;
    assert(r == 1);

    nums = {-5,-6,-7,-2,-1,0,-3};
    cout << "{-5,-6,-7,-2,-1,0,-3}" << endl;
    r = s.firstMissingPositive(nums);
    cout << "result " << r << endl;
    assert(r == 1);

    nums = {1,2,3,4,5,6,7,8,9,10};
    cout << "{1,2,3,4,5,6,7,8,9,10}" << endl;
    r = s.firstMissingPositive(nums);
    cout << "result " << r << endl;
    assert(r == 11);



    return 0;
}
