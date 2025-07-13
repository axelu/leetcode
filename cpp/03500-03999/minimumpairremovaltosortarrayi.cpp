
// 3507. Minimum Pair Removal to Sort Array I
// https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/





class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        // 1 <= nums.length <= 50

        // brute force
        int ops = 0;
        while( true ) {
            bool is_nondecreasing = true;
            for(int i = 1; i < nums.size() && is_nondecreasing == true; ++i) {
                if( nums[i-1] > nums[i] ) {
                    is_nondecreasing = false;
                    break;
                }
            }
            if( is_nondecreasing )
                return ops;

            // get adjacent pair with minimum sum
            int sum = INT_MAX;
            int idx = -1;
            for(int i = 0; i < nums.size()-1; ++i) {
                if( nums[i] + nums[i+1] < sum ) {
                    sum = nums[i] + nums[i+1];
                    idx = i;
                }
            }
            nums[idx] = sum;
            auto it = nums.begin();
            advance(it, idx+1);
            nums.erase(it);
            ++ops;
        }

        return ops;
    }
};
