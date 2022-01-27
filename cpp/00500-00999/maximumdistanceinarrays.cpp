
// 624. Maximum Distance in Arrays
// https://leetcode.com/problems/maximum-distance-in-arrays/





class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int n = arrays.size();

        int mn = arrays[0][0];
        int mx = arrays[0][arrays[0].size()-1];
        int ans = 0;

        int lmx,lmn;
        for(int i = 1; i < n; ++i) {
            lmn = arrays[i][0];
            lmx = arrays[i][arrays[i].size()-1];
            ans = max({ans,abs(mx-lmn),abs(lmx-mn)});
            mn = min(mn,lmn);
            mx = max(mx,lmx);
        }

        return ans;
    }
};
