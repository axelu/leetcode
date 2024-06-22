
// 2970. Count the Number of Incremovable Subarrays I
// https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/




class Solution {
private:

    int mem[50][50];

    bool is_strictly_increasing(vector<int>& nums, int s, int e) {
        if( mem[s][e] != -1 )
            return mem[s][e];

        for(int k = s+1; k <= e; ++k)
            if( nums[k-1] >= nums[k] )
                return mem[s][e] = false;

        return mem[s][e] = true;
    }

public:
    int incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 50

        int ans = 0;

        // cache answer for subarrays
        memset(mem,-1,sizeof mem);
        // constraint is small, for larger constraint we can step through
        // precalculating the answer efficiently
        for(int i = 0; i < n; ++i)
            mem[i][i] = 1;
        for(int l = 2; l <= n; ++l)
            for(int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;

                if( !mem[i][j-1] )
                    mem[i][j] = 0;
                else
                    mem[i][j] = nums[j-1] < nums[j];
            }

        for(int l = 1; l <= n; ++l) {
            // we slide a window of length l over nums
            // if the remainder of nums to the left and right of that sliding window
            // represents a strictly increasing array, then for increment our answer

            for(int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;
                // cout << "l " << l << " i " << i << " j " << j << endl;

                bool is_prefix_strictly_increasing = true;
                if( i > 0 ) {
                    int prefix_start = 0;
                    int prefix_end = i-1;
                    // is_prefix_strictly_increasing = is_strictly_increasing(nums,prefix_start,prefix_end);
                    is_prefix_strictly_increasing = mem[prefix_start][prefix_end];
                }

                if( !is_prefix_strictly_increasing )
                    continue;

                bool is_suffix_strictly_increasing = true;
                if( j < n-1 ) {
                    int suffix_start = j+1;
                    int suffix_end = n-1;
                    // is_suffix_strictly_increasing = is_strictly_increasing(nums,suffix_start,suffix_end);
                    is_suffix_strictly_increasing = mem[suffix_start][suffix_end];
                }

                if( !is_suffix_strictly_increasing )
                    continue;

                // we need to check if the last element of prefix is less then 1st element of suffix
                if( i > 0 && j < n-1 ) {
                    if( nums[i-1] < nums[j+1] )
                        ++ans;
                } else {
                    ++ans;
                }
            }
        }

        return ans;
    }
};
