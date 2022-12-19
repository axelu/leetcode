
// 2293. Min Max Game
// https://leetcode.com/problems/min-max-game/



class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        int n = nums.size(); // even
        while( n > 1 ) {
            int n_new = n/2;
            for(int i = 0; i < n_new; ++i) {
                if( i % 2 == 0 )  // even
                    nums[i] = min(nums[2*i],nums[2*i+1]);
                else             // odd
                    nums[i] = max(nums[2*i],nums[2*i+1]);
            }
            n = n_new;
        }

        return nums[0];
    }
};
