
// 3101. Count Alternating Subarrays
// https://leetcode.com/problems/count-alternating-subarrays/





class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1LL;

        long long ans = (long long)n;  // subarrays of length 1

        int i = 0;
        for(int j = 1; j < n; ++j) {

            if( nums[j-1] == nums[j] ) {
                // alternating array ends at j-1
                long long l = j - i; // (j-1) - i + 1 -> j - i;
                ans += (l * (l+1)/2.0) - l;

                i = j;
            }
        }
        // finish up
        long long l = n - i;
        ans += (l * (l+1)/2.0) - l;



        return ans;
    }
};
