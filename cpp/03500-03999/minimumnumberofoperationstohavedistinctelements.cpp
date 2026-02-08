
// 3779. Minimum Number of Operations to Have Distinct Elements
// https://leetcode.com/problems/minimum-number-of-operations-to-have-distinct-elements/



class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5
        if( n == 1 )
            return 0;
        if( n == 2 )
            return nums[0] == nums[1] ? 1 : 0;

        // 1 <= nums[i] <= 1e5
        int freq[100001]; memset(freq, 0, sizeof freq);
        int dups = 0;
        for(int x: nums) {
            ++freq[x];
            if( freq[x] == 2 )
                ++dups;
        }
        if( dups == 0 )
            return 0;

        int ops = 0;
        for(int i = 0; n-i >= 3; ) {
            ++ops;
            // we have 3 left, we need to remove 3
            --freq[nums[i]];
            if( freq[nums[i]] == 1 )
                --dups;
            ++i;
            --freq[nums[i]];
            if( freq[nums[i]] == 1 )
                --dups;
            ++i;
            --freq[nums[i]];
            if( freq[nums[i]] == 1 )
                --dups;
            ++i;
            if( dups == 0 )
                return ops;
        }

        // if we are here, we have 2 left that are the same
        return ops + 1;
    }
};
