
// 628. Maximum Product of Three Numbers
// https://leetcode.com/problems/maximum-product-of-three-numbers/



class Solution {
private:
    int _maximumProduct(vector<int>& nums) {
        int n = nums.size(); // 3 <= nums.length <= 6
        int res = INT_MIN;
        int ixj;
        for(int i = 0; i < n-2; ++i) {
           for(int j = i+1; j < n-1; ++j) {
               ixj = nums[i]*nums[j];
               for(int k = j+1; k < n; ++k) {
                  res = max(res,ixj*nums[k]);
               }
           }
        }
        return res;
    }

public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size(); // 3 <= nums.length <= 10^4
        if( n <= 6 ) return _maximumProduct(nums);

        sort(nums.begin(),nums.end());
        vector<int> v(6);
        v[0] = nums[0];
        v[1] = nums[1];
        v[2] = nums[2];
        v[3] = nums[n-3];
        v[4] = nums[n-2];
        v[5] = nums[n-1];
        return _maximumProduct(v);
    }
};
