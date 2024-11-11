
// 3301. Maximize the Total Height of Unique Towers
// https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/





class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        int n = maximumHeight.size();

        long long ans = 0LL;

        sort(maximumHeight.begin(),maximumHeight.end());

        long long cur = INT_MAX;
        for(int i = n-1; i >= 0; --i) {
            cur = min(cur-1, (long long)maximumHeight[i]);
            if( cur == 0LL )
                return -1LL;

            ans += cur;
        }

        return ans;
    }
};
