
// 2190. Most Frequent Number Following Key In an Array
// https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/



class Solution {
public:
    int mostFrequent(vector<int>& nums, int key) {
        int cnt[1001];memset(cnt,0,sizeof cnt);

        for(int i = 0; i < nums.size() - 1; ++i)
            if( nums[i] == key )
                ++cnt[nums[i+1]];

        int ans;
        int mx = 0;
        for(int i = 1; i <= 1000; ++i)
            if( cnt[i] > mx ) {
                mx = cnt[i];
                ans = i;
            }

        return ans;
    }
};
