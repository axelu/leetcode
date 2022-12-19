
// 2341. Maximum Number of Pairs in Array
// https://leetcode.com/problems/maximum-number-of-pairs-in-array/


class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        int cnt[101];memset(cnt,0,sizeof cnt);
        for(int x: nums)
            ++cnt[x];

        int a = 0;
        int b = 0;
        for(int i = 0; i <= 100; ++i) {
            a += cnt[i]/2;
            b += cnt[i]%2;
        }

        return {a,b};
    }
};
