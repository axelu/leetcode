
// Subarray Sum Equals K
// https://leetcode.com/problems/subarray-sum-equals-k/
// only the solution with the map does not run into TLE error


#include <iostream>
#include <cassert>

#include <vector>
#include <unordered_map>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    int _bf(vector<int>& nums, int k) { // Brute Force
        int r = 0;

        for(auto itl = nums.begin(); itl != nums.end(); ++itl) {
            // cout << "itl pos " << distance(nums.begin(), itl) << endl;
            for(auto itr = itl; itr != nums.end(); ++itr) {
                // cout << "itr pos " << distance(nums.begin(), itr) << endl;
                int sum = 0;
                for (auto it = itl; it != itr + 1; ++it) {
                    // cout << "it pos  " << distance(nums.begin(), it) << endl;
                    sum += *it;
                }
                if( sum == k ) ++r;
            }
        }
        return r;
    }

    int _rs(vector<int>& nums, int k) { // Running Sum
        int r = 0;

        int sum;
        auto itl = nums.begin();
        auto itr = itl;
        for(; itl != nums.end(); ++itl) {
            sum = *itl;
            if( sum == k ) ++r;
            for(itr = itl + 1; itr != nums.end(); ++itr) {
                sum += *itr;
                if( sum == k ) ++r;
            }
            itr = itl;
        }

        return r;
    }

    int _cs(vector<int>& nums, int k) { // Cumulative Sum
        int r = 0;

        auto n = nums.size();
        vector<int> cs;
        auto itb = nums.begin();
        for (auto itl = itb; itl != nums.end(); ++itl) {
            for(auto itr = itl; itr != nums.end(); ++itr) {
                int s = *itl;
                auto ridx = distance(itb,itr);
                if( cs.size() < n ) {
                    if( ridx > 0 ) {
                        cs.push_back(*itr + cs[ridx - 1]);
                    } else {
                        cs.push_back(s);
                    }
                }
                if( distance(itl, itr) > 0 )
                    s += cs[distance(itb,itr)] - cs[distance(itb,itl)];
                if( s == k )
                    ++r;
            }
        }

        return r;
    }

    int _mp(vector<int>& nums, int k) {
        int r = 0;

        int sum = 0;

        unordered_map<int,int> mp; // sum, number of occurences of sum
        mp.insert({0, 1});

        for(auto it = nums.begin(); it != nums.end(); ++it) {
            sum += *it;

            auto f = mp.find(sum - k);
            if( f != mp.end() )
                r += f->second;

            auto p = mp.insert({sum,1});
            if( !p.second )
                ++p.first->second;
        }

        return r;
    }

public:
    int subarraySum(vector<int>& nums, int k) {
        // 1 <= nums.length <= 20000
        // -1000 <= nums[i] <= 1000
        // -1e7 <= k <= 1e7
        // min sum 20000 * -1000 = -20000000
        // max sum 20000 *  1000 =  20000000
        // int large enough to hold sum

        if( nums.size() == 1 )
            return nums[0] == k ? 1 : 0;

        // return _bf(nums,k);
        // return _rs(nums,k);
        // return _cs(nums,k);
        return _mp(nums,k);

    }
};
/*
int main() {
    Solution s;
    vector<int> nums;
    int k;
    int r;

    nums = {1,1,1};
    cout << "{1,1,1}" << endl;
    k = 2;
    r = s.subarraySum(nums,k);
    cout << "result " << r << endl;
    assert(r == 2);

    nums = {1,2,1};
    cout << "{1,2,1}" << endl;
    k = 2;
    r = s.subarraySum(nums,k);
    cout << "result " << r << endl;
    assert(r == 1);

    nums = {3,4,7,2,-3,1,4,2};
    cout << "{3,4,7,2,-3,1,4,2}" << endl;
    k = 7;
    r = s.subarraySum(nums,k);
    cout << "result " << r << endl;
    assert(r == 4);

    return 0;
}*/
