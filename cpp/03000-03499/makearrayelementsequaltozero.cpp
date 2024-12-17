
// 3354. Make Array Elements Equal to Zero
// https://leetcode.com/problems/make-array-elements-equal-to-zero/



class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();

        if( n == 1 )
            return 2;


        // oberservation
        //   if we are at a 0
        //   let l be the sum to our left
        //   let r be the sum to our right
        //   if abs(l-r) == 0 then 2
        //   if abs(l-r) == 1 then 1
        //   else 0

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <=n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int ans = 0;
        int r = 0;
        for(int i = n-1; i >= 0; --i) {
            if( nums[i] == 0 ) {
                // the sum left of us is prefixSum[i]
                int d = abs(prefixSum[i] - r);
                if( d == 0 )
                    ans += 2;
                else if( d == 1 )
                    ans += 1;
            }
            r += nums[i];
        }

        return ans;
    }
};
