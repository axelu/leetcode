
// 2817. Minimum Absolute Difference Between Elements With Constraint
// https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/





class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        if( x == 0 )
            return 0;

        int n = nums.size();
        set<int> st;
        int ans = INT_MAX;
        for(int i = n - 1; i >= x && ans != 0; --i) {
            st.insert(nums[i]);

            int k = nums[i - x];
            auto lb = st.lower_bound(k);
            if( lb != st.end() ) {
                ans = min(ans, *lb - k);
                if( lb != st.begin() )
                    ans = min(ans, k - *prev(lb));
            } else {
                ans = min(ans, k - *st.rbegin());
            }
        }

        return ans;
    }
};
