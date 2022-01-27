
// 2113. Elements in Array After Removing and Replacing Elements
// https://leetcode.com/problems/elements-in-array-after-removing-and-replacing-elements/


class Solution {
public:
    vector<int> elementInNums(vector<int>& nums, vector<vector<int>>& queries) {
        int nums_sz = nums.size();

        int n =  queries.size();
        vector<int> ans(n);
        int time,index,rem,curr_sz;
        for(int i = 0; i < n; ++i) {
            time  = queries[i][0];
            index = queries[i][1];

            rem = time % (nums_sz*2);
            if( rem == 0 ) {
                ans[i] = nums[index];
                continue;
            }

            if( rem <= nums_sz ) {
                curr_sz = nums_sz - rem;
                if( index >= curr_sz ) {
                    ans[i] = -1;
                } else {
                    ans[i] = nums[index+rem];
                }
            } else { // rem < 0
                curr_sz = rem - nums_sz;
                if( index >= curr_sz ) {
                    ans[i] = -1;
                } else {
                    ans[i] = nums[index];
                }
            }
        }

        return ans;
    }
};
