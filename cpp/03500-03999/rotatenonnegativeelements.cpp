
// 3819. Rotate Non Negative Elements
// https://leetcode.com/problems/rotate-non-negative-elements/



class Solution {
public:
    vector<int> rotateElements(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> nonnegval;
        vector<int> nonnegpos;
        for(int i = 0; i < n; ++i) {
            if( nums[i] >= 0 ) {
                nonnegval.push_back(nums[i]);
                nonnegpos.push_back(i);
            }
        }
        int l = nonnegpos.size();
        if( l == 0 )
            return nums;

        rotate(nonnegval.begin(), nonnegval.begin() + (k % l), nonnegval.end());

        for(int i = 0; i < nonnegval.size(); ++i)
            nums[nonnegpos[i]] = nonnegval[i];

        return nums;
    }
};
