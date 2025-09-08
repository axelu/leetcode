
// 3637. Trionic Array I
// https://leetcode.com/problems/trionic-array-i/




class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if( n < 4 )
            return false;

        // 0 < p < q < n-1
        // 0 < p < n-2 => pmin = 1, pmax = n-3
        // 1 < q < n-1 => qmin = 2, qmax = n-2

        // find index p, which is our left most peak
        // and must up to that point be strictly increasing
        int p = -1;
        for(int i = 1; i < n-2; ++i) {
            if( nums[i-1] >= nums[i] )
                return false;
            // peek ahead
            if( nums[i] == nums[i+1] )
                return false;
            if( nums[i] > nums[i+1] ) {
                p = i;
                break;
            }
        }
        if( p == -1 )
            return false;

        // find index q
        int q = -1;
        for(int i = p+1; i < n-1; ++i) {
            // peek ahead
            if( nums[i] == nums[i+1] )
                return false;
            if( nums[i] < nums[i+1] ) {
                q = i;
                break;
            }
        }
        if( q == -1 )
            return false;

        // finish
        // check if strictly increasing
        for(int i = q; i < n-1; ++i)
            if( nums[i] >= nums[i+1] )
                return false;


        return true;
    }
};
