
// 2216. Minimum Deletions to Make Array Beautiful
// https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/



class Solution {
public:
    int minDeletion(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        // one way or another, going from left to right,
        // if we are at an even index and the following
        // value is the same, we need to delete
        int ans = 0;
        int real_idx = 0;
        int i = 1;
        int j = 0;
        for(; i < n; ++i) {
            if( real_idx % 2 == 0 ) {
                if( nums[j] == nums[i] ) {
                    ++ans;
                    continue;
                } else {
                    j = i;
                    ++real_idx;
                }
            } else {
                j = i;
                ++real_idx;
            }
        }

        //cout << "i " << i << " j " << j << " real_idx " << real_idx << endl;
        if( real_idx % 2 == 0 )
           ++ans;

        return ans;
    }
};
