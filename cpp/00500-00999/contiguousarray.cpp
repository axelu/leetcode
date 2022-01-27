
// 525. Contiguous Array
// https://leetcode.com/problems/contiguous-array/


// Approach #2 Using Extra Array
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        size_t n = nums.size();

        int a[2*n+1];memset(a,-2,sizeof a);
        a[n] = -1;

        int ans = 0;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            cnt += nums[i] == 1 ? 1 : -1;
            if( a[cnt+n] >= -1 ) ans = max(ans,i-a[cnt+n]);
            else a[cnt+n] = i; // record 1st idx we encountered count
        }
        return ans;
    }
};
