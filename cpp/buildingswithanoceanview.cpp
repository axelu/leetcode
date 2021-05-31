
// 1762. Buildings With an Ocean View
// https://leetcode.com/problems/buildings-with-an-ocean-view/



class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size();
        vector<int> ans = {n-1};
        if( n == 1 ) return ans;

        ans.reserve(n); // worst case
        int mx = heights[n-1];
        for(int i = n-2; i >= 0; --i) {
            if( heights[i] > mx ) {
                ans.push_back(i);
                mx = heights[i];
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
