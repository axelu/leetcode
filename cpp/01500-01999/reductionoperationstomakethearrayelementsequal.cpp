
// 1887. Reduction Operations to Make the Array Elements Equal
// https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/



class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        sort(nums.begin(),nums.end());

        int n = nums.size();
        int ans = 0;
        for(int i = n-2; i >= 0; --i)
            if( nums[i] != nums[i+1] )
                ans += n - (i+1);

        return ans;
    }
};
