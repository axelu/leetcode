
// 2931. Maximum Spending After Buying Items
// https://leetcode.com/problems/maximum-spending-after-buying-items/






class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        int m = values.size();      // rows = shops
        int n = values[0].size();   // cols = items

        long long ans = 0LL;

        int l[m]; // rightmost idx in row i that we can buy
        for(int i = 0; i < m; ++i)
            l[i] = n-1;

        for(long long day = 1; day <= m*n; ++day) {

            int mn = INT_MAX;
            int r; // row that we will purchase the item from on day

            for(int i = 0; i < m; ++i) {
                if( l[i] >= 0 ) {
                    int t = values[i][l[i]];
                    if( t < mn ) {
                        mn = t;
                        r = i;
                    }
                }
            }
            // cout << "day " << day << " buy row " << r << " item " << l[r] << endl;
            ans += day * values[r][l[r]];
            --l[r];
        }

        return ans;
    }
};
