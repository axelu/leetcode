
// 1674. Minimum Moves to Make Array Complementary
// https://leetcode.com/problems/minimum-moves-to-make-array-complementary/

// delivers correct results, but TLE

#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <climits>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        size_t n = nums.size();
        if( n == 2 ) return 0;
        int n2 = n/2;

        unordered_set<int> sums;
        int a,b,t,oneMoveMin,oneMoveMax;
        array<int,3> w[n2];
        int mx = 0, mn = 100001;
        for(int i = 0; i < n2; ++i) {
            a = nums[i];
            b = nums[n-1-i];
            t = a + b;
            mn = min(mn,t);
            mx = max(mx,t);
            sums.insert(t);
            oneMoveMax = max(a,b) + limit;
            oneMoveMin = min(a,b) + 1;
            w[i] = {t,oneMoveMax,oneMoveMin};
        }
        if( mn == mx ) return 0;

        int ans = INT_MAX;
        int r;
        int T;
        for(auto it = sums.begin(); it != sums.end(); ++it) {
            T = *it;
            r = 0;
            for(int i = 0; i < n2; ++i) {
                t = w[i][0];
                if( t < T ) {
                    // we need to increase a or b or both
                    r += w[i][1] < T ? 2 : 1;
                } else if( t > T ) {
                    // we need to decrease a or b or both
                    r += w[i][2] > T ? 2 : 1;
                }
            }

            ans = min(ans,r);
        }

        return ans;
    }
};

int main() {

    Solution s;
    vector<int> nums;
    int limit;
    int r;

    // case 44 / 110
    nums = {28,50,76,80,64,30,32,84,53,8};
    limit = 84;
    r = s.minMoves(nums,limit);
    cout << r << endl;
    assert(4 == r);

    return 0;
}
