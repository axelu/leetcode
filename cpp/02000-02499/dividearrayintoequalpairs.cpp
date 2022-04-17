
// 2206. Divide Array Into Equal Pairs
// https://leetcode.com/problems/divide-array-into-equal-pairs/



class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int cnt[501];memset(cnt,0,sizeof cnt);

        for(int x : nums)
            ++cnt[x];

        for(int i = 1; i < 501; ++i)
            if( cnt[i] & 1 )
                return false;

        return true;
    }
};
