
// 3151. Maximum Number of Upgradable Servers
// https://leetcode.com/problems/maximum-number-of-upgradable-servers/





class Solution {
private:

    int search(int s, int e, long count, long upgrade, long sell, long money) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        long upgrade_cost = mid * upgrade;
        long money_we_have = money + ((count - mid) * sell);

        if( upgrade_cost <= money_we_have ) {
            // can we do better?
            int t = search(mid+1, e, count, upgrade, sell, money);
            return t != -1 ? t : mid;
        }

        return search(s, mid-1, count, upgrade, sell, money);
    }



public:
    vector<int> maxUpgrades(vector<int>& count, vector<int>& upgrade, vector<int>& sell, vector<int>& money) {
        // count.length == upgrade.length == sell.length == money.length
        int n = count.size();

        vector<int> ans(n);

        // for data center i, our answer is between 0 and count[i]
        for(int i = 0; i < n; ++i)
            ans[i] = search(0, count[i], count[i], upgrade[i], sell[i], money[i]);

        return ans;
    }
};
