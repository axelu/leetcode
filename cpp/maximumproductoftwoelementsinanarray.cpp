
// Maximum Product of Two Elements in an Array
// https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // if( nums.size() == 2 ) return (nums[0]-1)*(nums[1]-1);

        sort(nums.begin(), nums.end());
        return (*(nums.end()-1)-1)*(*(nums.end()-2)-1);
    }
};
