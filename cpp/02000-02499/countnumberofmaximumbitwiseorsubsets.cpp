
// 2044. Count Number of Maximum Bitwise-OR Subsets
// https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/




class Solution {
private:
    int mx,cnt;

    void genSubsequences(vector<int>& nums, int n, int i, int r) {
        if( i == n ) {
            if( r > mx ) {
                mx  = r;
                cnt = 1;
            } else if( r == mx ) {
                ++cnt;
            }
        } else {
            // we have a choice
            // don't include int at current index
            genSubsequences(nums,n,i+1,r);

            // include int at current index
            r |= nums[i];
            genSubsequences(nums,n,i+1,r);
        }
        return;
    }


public:
    int countMaxOrSubsets(vector<int>& nums) {
        int n = nums.size();

        mx  = 0;
        cnt = 0;

        genSubsequences(nums,n,0,0);

        return cnt;
    }
};
