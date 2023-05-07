
// 2610. Convert an Array Into a 2D Array With Conditions
// https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/




class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        int n = nums.size();

        map<int,int> mp;
        // we need at least as many rows as we have count of a single number
        int mx_occurence = 0;
        for(int x: nums) {
            ++mp[x];
            mx_occurence = max(mx_occurence, mp[x]);
        }

        vector<vector<int>> ans(mx_occurence);

        for(auto it = mp.begin(); it != mp.end(); ++it) {

            for(int i = 0; i < it->second; ++i)
                ans[i].push_back(it->first);

        }

        return ans;
    }
};
