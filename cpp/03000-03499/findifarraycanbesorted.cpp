
// 3011. Find if Array Can Be Sorted
// https://leetcode.com/problems/find-if-array-can-be-sorted/





class Solution {
private:
    bool is_sorted(vector<int>& nums) {
        // 1 < nums.size()
        int pre = *nums.begin();
        for(auto it = next(nums.begin()); it != nums.end(); ++it) {
            if( *it < pre )
                return false;
            pre = *it;
        }
        return true;
    }

    int count_set_bits(int i) {
        int count = 0;
        while(i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 || is_sorted(nums) )
            return true;

        // think of nums as blocks of numbers
        // a new block starts when the number of set bits changes
        // we then need to compare the max of the prior block to the min of the current block
        // if max prior block <= min of current block then we can continue
        int prior_block_set_bits = -1;
        int prior_block_min = -1;
        int prior_block_max = -1;
        int current_block_set_bits = count_set_bits(nums[0]); // cout << "set bits nums[0] " << current_block_set_bits << endl;
        int current_block_min = nums[0];
        int current_block_max = nums[0];
        for(int i = 1; i < n; ++i) {
            int set_bits = count_set_bits(nums[i]);
            // cout << "set bits nums[" << i << "] " << set_bits << endl;

            if( set_bits != current_block_set_bits ) {
                // a new block starts at i

                if( prior_block_set_bits != -1 )
                    if( current_block_min < prior_block_max )
                        return false;

                prior_block_set_bits = current_block_set_bits;
                prior_block_min = current_block_min;
                prior_block_max = current_block_max;

                current_block_set_bits = set_bits;
                current_block_min = nums[i];
                current_block_max = nums[i];

            } else {
                current_block_min = min(current_block_min, nums[i]);
                current_block_max = max(current_block_max, nums[i]);
            }
        }
        // finish up
        if( prior_block_set_bits != -1 )
            if( current_block_min < prior_block_max )
                return false;

        return true;
    }
};
