
// 2903. Find Indices With Index and Value Difference I
// https://leetcode.com/problems/find-indices-with-index-and-value-difference-i/





class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        int n = nums.size();

        // brute force
        for(int i = 0; i <= (n-1) - indexDifference; ++i)
            for(int j = i + indexDifference; j < n; ++j)
                if( abs(nums[i] - nums[j]) >= valueDifference )
                    return {i,j};

        return {-1,-1};
    }
};
