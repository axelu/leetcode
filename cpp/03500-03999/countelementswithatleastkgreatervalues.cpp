
// 3759. Count Elements With at Least K Greater Values
// https://leetcode.com/problems/count-elements-with-at-least-k-greater-values/



class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        map<int,int> mp;
        for(int x: nums)
            ++mp[x];

        int mp_sz = mp.size();
        int suffixSum = 0; // "0-indexed"
        int ans = 0;
        for(auto itr = mp.rbegin(); itr != mp.rend(); ++itr) {
            if( suffixSum >= k )
                ans += itr->second;
            suffixSum += itr->second;
        }

        return ans;
    }
};
