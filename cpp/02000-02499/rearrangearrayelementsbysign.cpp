
// 2149. Rearrange Array Elements by Sign
// https://leetcode.com/problems/rearrange-array-elements-by-sign/



class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        int pos[n/2];
        int neg[n/2];
        int i = 0, j = 0;
        for(int k = 0; k < n; ++k)
            if( nums[k] > 0 ) {
                pos[i] = nums[k];
                ++i;
            } else {
                neg[j] = nums[k];
                ++j;
            }

        i = 0; j = 0;
        for(int k = 0; k < n; ++k) {
            if( !(k%2) ) {
                nums[k] = pos[i];
                ++i;
            } else {
                nums[k] = neg[j];
                ++j;
            }
        }

        return nums;
    }
};
