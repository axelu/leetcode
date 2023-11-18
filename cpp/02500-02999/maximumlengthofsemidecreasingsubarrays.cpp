
// 2863. Maximum Length of Semi-Decreasing Subarrays
// https://leetcode.com/problems/maximum-length-of-semi-decreasing-subarrays/




class Solution {
public:
    int maxSubarrayLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        map<int,pair<int,int>,greater<int>> mp; // sorted desc; nums[i], {1st occurence, last occurence}
        for(int i = 0; i < n; ++i) {
            auto p = mp.insert({nums[i],{i,i}});
            if( !p.second )
                p.first->second.second = i;
        }

        /*
        for(auto it = mp.begin(); it != mp.end(); ++it)
            cout << it->first << ":" << it->second.first << "," <<  it->second.second << " ";
        cout << endl;
        */

        int mn_idx = mp.begin()->second.first;
        for(auto it = next(mp.begin()); it != mp.end(); ++it) {
            if( mn_idx < it->second.second )
                ans = max(ans, it->second.second - mn_idx + 1);
            mn_idx = min(mn_idx, it->second.first);
        }

        return ans;
    }
};
