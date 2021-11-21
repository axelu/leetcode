
// 1852. Distinct Numbers in Each Subarray
// https://leetcode.com/problems/distinct-numbers-in-each-subarray/




class Solution {
public:
    vector<int> distinctNumbers(vector<int>& nums, int k) {
        int n = nums.size();

        int cnt[100001];memset(cnt,0,sizeof cnt);

        vector<int> ans(n-k+1);

        int c = 0;
        int l = 0,r = k-1;
        for(int i = 0; i < n; ++i) {
            if( i < k ) {
                ++cnt[nums[i]];
                if( cnt[nums[i]] == 1 ) ++c;
                if( i == k-1 ) {
                    // cout << "l " << l << " r " << r << endl;
                    ans[l] = c;
                    ++l;
                    ++r;
                }
                continue;
            }
            // cout << "l " << l << " r " << r << endl;
            --cnt[nums[l-1]];
            if( cnt[nums[l-1]] == 0 ) --c;
            ++cnt[nums[i]];
            if( cnt[nums[i]] == 1 ) ++c;
            ans[l] = c;
            ++l;
            ++r;
        }
        return ans;
    }
};
