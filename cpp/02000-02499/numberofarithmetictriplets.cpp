
// 2367. Number of Arithmetic Triplets
// https://leetcode.com/problems/number-of-arithmetic-triplets/


class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int ans = 0;
        
        int n = nums.size();
        for(int i = 0; i < n-2; ++i)
            for(int j = i+1; j < n-1; ++j) {
                if( nums[j] - nums[i] == diff ) {
                    for(int k = j+1; k < n; ++k)
                        if( nums[k] - nums[j] == diff ) {
                            ++ans;
                            break;
                        } else if( nums[k] - nums[j] > diff ) {
                            break;
                        }
                    break;
                } else if( nums[j] - nums[i] > diff ) {
                    break;
                }
            }
        
        
        return ans;
    }
};
