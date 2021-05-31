
// 1561. Maximum Number of Coins You Can Get
// https://leetcode.com/problems/maximum-number-of-coins-you-can-get/




class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(),piles.end(),greater<int>());
        int ans = 0;
        for(int i = 1; i < piles.size()/3*2; i += 2)
            ans += piles[i];

        return ans;
    }
};
