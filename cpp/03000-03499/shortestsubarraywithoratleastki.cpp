
// 3095. Shortest Subarray With OR at Least K I
// https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/





class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();

        // small constraints -> brute force

        int ans = INT_MAX;

        int t[n]; memset(t,0,sizeof t); // OR of subarray starting at i
        for(int l = 1; l <= n && ans == INT_MAX; ++l) {
            for(int i = 0; i <= n-l && ans == INT_MAX; ++i) {
                int j = i + l - 1;
                t[i] |= nums[j];
                if( t[i] >= k )
                    ans = l;
            }
        }

        return ans != INT_MAX ? ans : -1;
    }
};
