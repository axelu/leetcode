
// 3741. Minimum Distance Between Three Equal Elements II
// https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5

        int ans = INT_MAX;

        // observation:
        //    let i <= j <= k and nums[i] == nums[j] == nums[k]
        //    then our distance (k-i) * 2
        //    so we can search for the smallest distance
        //    while standing at i if we knew the next k

        int nxt[100001]; memset(nxt,-1,sizeof nxt);
        int nxtnxt[100001]; memset(nxtnxt,-1,sizeof nxtnxt);
        for(int i = n-1; i >= 0; --i) {
            int x = nums[i];
            if( nxtnxt[x] != -1 )
                ans = min(ans, (nxtnxt[x] - i) * 2);
            nxtnxt[x] = nxt[x];
            nxt[x] = i;
        }

        return ans != INT_MAX ? ans : -1;
    }
};
