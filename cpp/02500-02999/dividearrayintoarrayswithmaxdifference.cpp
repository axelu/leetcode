
// 2966. Divide Array Into Arrays With Max Difference
// https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/





class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        int n = nums.size(); // n is a multiple of 3
        int partitions = n / 3;

        sort(nums.begin(),nums.end());

        vector<vector<int>> ans(partitions,vector<int>(3));
        for(int partition = 0; partition < partitions; ++partition) {

            int i = partition * 3;
            int i_max = i + 2;
            if( nums[i_max] - nums[i] > k )
                return {};
            for(int j = 0; j < 3; ++j, ++i)
                ans[partition][j] = nums[i];
        }

        return ans;
    }
};
