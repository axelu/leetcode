
// 2964. Number of Divisible Triplet Sums
// https://leetcode.com/problems/number-of-divisible-triplet-sums/




class Solution {
public:
    int divisibleTripletCount(vector<int>& nums, int d) {
        int n = nums.size();
        if( n < 3 )
            return 0;

        int ans = 0;

        // brute force
        for(int i = 0; i <  n-2; ++i) {
            long nums_i = nums[i];
            for(int j = i+1; j < n-1; ++j) {
                long nums_i_plus_nums_j = nums_i + nums[j];
                for(int k = j+1; k < n; ++k)
                    if( (nums_i_plus_nums_j + nums[k]) % d == 0 )
                        ++ans;
            }
        }

        return ans;
    }
};
