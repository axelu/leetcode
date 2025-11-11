
// 3737. Count Subarrays With Majority Element I
// https://leetcode.com/problems/count-subarrays-with-majority-element-i/



class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(); // 1 <= n <= 1000
        // 1 <= nums[i] <= 1e9
        // 1 <= target <= 1e9

        int ans = 0;

        // advanced alternating loop (still dumb brute force loop)
        // sliding window alternating expanding then shrinking
        int cnt = 0; // count of target in current window
        for(int i = 0; i < n; ++i) {
            int l = 1;
            int j = i;
            for(; j < n; ++j,++l) {
                if( nums[j] == target )
                    ++cnt;
                if( cnt > l/2 )
                    ++ans;
            }

            if( nums[i] == target )
                --cnt;
            i += 1;
            if( i == n )
                break;
            l -= 2; // because loop advanced it
            j -= 1; // because loop advanced it

            for(; j >= i; --j,--l) {
                if( cnt > l/2 )
                    ++ans;
                if( nums[j] == target )
                    --cnt;
            }
        }

        return ans;
    }
};
