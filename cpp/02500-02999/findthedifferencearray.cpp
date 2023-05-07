
// 2670. Find the Distinct Difference Array
// https://leetcode.com/problems/find-the-distinct-difference-array/



class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return {1};

        vector<int> ans(n);

        int seen[51];memset(seen,0,sizeof seen);

        vector<int> b(n+1); // number of distinct elements in suffix
        b[n] = 0;
        b[n-1] = 1;
        seen[nums[n-1]] = 1;
        for(int i = n-2; i >= 0; --i) {
            if( seen[nums[i]] ) {
                b[i] = b[i+1];
            } else {
                seen[nums[i]] = 1;
                b[i] = b[i+1] + 1;
            }
        }

        memset(seen,0,sizeof seen);

        int pre = 0;        // number of distinct elements in prefix
        for(int i = 0; i < n; ++i) {
            if( !seen[nums[i]] ) {
                seen[nums[i]] = 1;
                ++pre;
            }
            ans[i] = pre - b[i+1];
        }

        return ans;
    }
};
