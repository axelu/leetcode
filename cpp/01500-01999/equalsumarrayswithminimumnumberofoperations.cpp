
// 1775. Equal Sum Arrays With Minimum Number of Operations
// https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/


class Solution {
private:
    int solve(int diff, int k) {
        int ret = diff/k;
        if( diff % k != 0 )
            ++ret;
        return ret;
    }

public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        // greedy, with every move we want to make the biggest difference,
        // because we are ask to return min number of moves so that sum1 becomes equal sum2
        // example: change 1 to 6, we can achieve a max difference of +5 with on move
        //          change 2 to 6, we can achieve a max difference of +4 with one move only

        int _cnt1[7];memset(_cnt1,0,sizeof _cnt1);
        int sum1 = 0;
        for(int x: nums1) {
            ++_cnt1[x];
            sum1 += x;
        }

        int _cnt2[7];memset(_cnt2,0,sizeof _cnt2);
        int sum2 = 0;
        for(int x: nums2) {
            ++_cnt2[x];
            sum2 += x;
        }

        if( sum1 == sum2 )
            return 0;

        // lets make sum1 the smaller sum, swap it needed
        int * cnt1;
        int * cnt2;
        if( sum2 < sum1 ) {
            cnt1 = _cnt2;
            cnt2 = _cnt1;
            int t = sum1;
            sum1 = sum2;
            sum2 = t;
        } else {
            cnt1 = _cnt1;
            cnt2 = _cnt2;
        }

        // we need to make sum1 bigger and sum2 smaller greedily
        int diff = sum2 - sum1;
        int ans = 0;

        // sum1: change all 1s to 6s, gaining +5 for each
        if( cnt1[1] * 5 >= diff )
            return ans + solve(diff,5);
        diff -= cnt1[1] * 5;
        ans += cnt1[1];

        // sum2: change all 6s to 1s, gaining -5 for each
        if( cnt2[6] * 5 >= diff )
            return ans + solve(diff,5);
        diff -= cnt2[6] * 5;
        ans += cnt2[6];

        // sum1: change all 2s to 6s, gaining +4 for each
        if( cnt1[2] * 4 >= diff )
            return ans + solve(diff,4);
        diff -= cnt1[2] * 4;
        ans += cnt1[2];

        // sum2: change all 5s to 1s, gaining -4 for each
        if( cnt2[5] * 4 >= diff )
            return ans + solve(diff,4);
        diff -= cnt2[5] * 4;
        ans += cnt2[5];

        // sum1: change all 3s to 6s, gaining +3 for each
        if( cnt1[3] * 3 >= diff )
            return ans + solve(diff,3);
        diff -= cnt1[3] * 3;
        ans += cnt1[3];

        // sum2: change all 4s to 1s, gaining -3 for each
        if( cnt2[4] * 3 >= diff )
            return ans + solve(diff,3);
        diff -= cnt2[4] * 3;
        ans += cnt2[4];

        // sum1: change all 4s to 6s, gaining +2 for each
        if( cnt1[4] * 2 >= diff )
            return ans + solve(diff,2);
        diff -= cnt1[4] * 2;
        ans += cnt1[4];

        // sum2: change all 3s to 1s, gaining -2 for each
        if( cnt2[3] * 2 >= diff )
            return ans + solve(diff,2);
        diff -= cnt2[3] * 2;
        ans += cnt2[3];

        // sum1: change all 5s to 6s, gaining +1 for each
        if( cnt1[5] * 1 >= diff )
            return ans + solve(diff,1);
        diff -= cnt1[5] * 1;
        ans += cnt1[5];

        // sum2: change all 2s to 1s, gaining -1 for each
        if( cnt2[2] * 1 >= diff )
            return ans + solve(diff,1);
        // diff -= cnt2[2] * 1;
        // ans += cnt2[2];

        return -1;
    }
};
