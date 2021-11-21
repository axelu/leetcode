
// 1966. Binary Searchable Numbers in an Unsorted Array
// https://leetcode.com/problems/binary-searchable-numbers-in-an-unsorted-array/





class Solution {
public:
    int binarySearchableNumbers(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        // get min
        set<int> rgtMin;

        for(int i = 0; i < n; ++i)
            rgtMin.insert(nums[i]);
        rgtMin.insert(INT_MAX);

        int ans = 0;

        int lftMax = INT_MIN;
        for(int i = 0; i < n; ++i) {
            rgtMin.erase(nums[i]);

            if( lftMax < nums[i] && *rgtMin.begin() > nums[i] )
                ++ans;

            lftMax = max(lftMax,nums[i]);
        }


        return ans;
    }
};
