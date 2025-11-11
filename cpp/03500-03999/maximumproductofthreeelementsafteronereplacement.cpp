
// 3732. Maximum Product of Three Elements After One Replacement
// https://leetcode.com/problems/maximum-product-of-three-elements-after-one-replacement/



class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int n = nums.size();

        int largest = INT_MIN;
        int secondlargest = INT_MIN;
        for(int i = 0; i < n; ++i) {
            if( abs(nums[i]) > largest ) {
                secondlargest = largest;
                largest = abs(nums[i]);
            } else if( abs(nums[i]) > secondlargest ) {
                secondlargest = abs(nums[i]);
            }
        }

        return (long long)largest * (long long)secondlargest * (long long)100000;
    }
};
