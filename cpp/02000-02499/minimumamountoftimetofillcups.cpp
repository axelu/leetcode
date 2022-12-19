
// 2335. Minimum Amount of Time to Fill Cups
// https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/


class Solution {
public:
    int fillCups(vector<int>& amount) {
        sort(amount.begin(),amount.end(),greater<int>());
        int ans = 0;
        while( amount[2] != 0 ) {
            ++ans;
            --amount[0];
            --amount[1];
            sort(amount.begin(),amount.end(),greater<int>());
        }

        return ans + amount[0];
    }
};
