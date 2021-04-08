
// 414. Third Maximum Number
// https://leetcode.com/problems/third-maximum-number/


class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return nums[0];
        if( n == 2 ) return nums[0] > nums[1] ? nums[0] : nums[1];

        long mx     = -2147483649;  // max aka larget element
        long scndMx = -2147483649;; // 2nd largest element
        long thrdMx = -2147483649;; // 3rd largets element
        long curr;
        for(int i = 0; i < n; ++i) {
            curr = (long)nums[i];
            if( curr > mx ) {
                thrdMx = scndMx;
                scndMx = mx;
                mx = curr;
            } else if( curr > scndMx && curr < mx ) {
                thrdMx = scndMx;
                scndMx = curr;
            } else if( curr > thrdMx && curr < scndMx ) {
                thrdMx = curr;
            }
        }
        return thrdMx != -2147483649 ? thrdMx : mx;
    }
};
