
// 2765. Longest Alternating Subarray
// https://leetcode.com/problems/longest-alternating-subarray/





class Solution {
public:
    int alternatingSubarray(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 100

        // small enough constraint, hence brute force
        int ans = -1;

        for(int i = 0; i < n-1; ++i) {
            int s0 = nums[i];
            int s1 = nums[i]+1;
            int m = 1;
            for(int j = i+1; j < n; ++j) {
                int l = j - i + 1;
                if( nums[j] == nums[i] + ( (l-1) % 2 ) )
                    ++m;
                else
                    break;
            }
            if( m > 1 )
                ans = max(ans,m);
        }

        return ans;
    }
};
