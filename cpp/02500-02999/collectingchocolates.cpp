
// 2735. Collecting Chocolates
// https://leetcode.com/problems/collecting-chocolates/




class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];

        // base line
        // collect all chocolates as is, meaning no rotation
        // record what it takes to collect each chocolate
        // rotate and keep recording min cost to collect each type
        long long ans = LLONG_MAX;
        vector<long long> mn(n,LLONG_MAX); // min it takes to collect chocolate of type i
        for(long long k = 0; k < n; ++k) {     // rotation
            // cout << k << " rotations" << endl;
            long long cost_rotation = k * x;
            long long cost = 0;

            for(int j = 0; j < n; ++j) {
                int i = ((j + k) % n); // type of chocolate at position j after k rotations
                // cout << "  pos " << j << " type " << i << endl;
                mn[i] = min(mn[i],(long long)nums[j]);
                cost += mn[i];
            }
            ans = min(ans,cost_rotation + cost);
        }

        return ans;
    }
};
