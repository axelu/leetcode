
// 2404. Most Frequent Even Element
// https://leetcode.com/problems/most-frequent-even-element/



class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,int> um;
        for(int i = 0; i < n; ++i)
            if( nums[i] % 2 == 0 )
                ++um[nums[i]];

        int mx_freq = 0;
        int ans = -1;
        for(auto it = um.begin(); it != um.end(); ++it)
            if( it->second > mx_freq ) {
                mx_freq = it->second;
                ans = it->first;
            } else if( it->second == mx_freq ) {
                if( it->first < ans )
                    ans = it->first;
            }

        return ans;
    }
};
