
// 1578. Minimum Deletion Cost to Avoid Repeating Letters
// https://leetcode.com/problems/minimum-deletion-cost-to-avoid-repeating-letters/


class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        size_t n = s.size();    // s.length == cost.length
        if( n == 1 ) return 0;  // 1 <= s.length, cost.length <= 10^5

        int r = 0;

        int cs, mx;
        int idx0 = 0;
        for(int idx1 = 1; idx1 < n; ++idx1) {
            if( s[idx0] != s[idx1] ) {
                if( idx1 - idx0 != 1 ) {
                    // get sum of cost [idx0,idx1), subtract maximum
                    cs = 0;
                    mx = 0;
                    for(int i = idx0; i < idx1; ++i) {
                        cs += cost[i];
                        mx = max(mx,cost[i]);
                    }
                    r += cs-mx;
                }
                idx0 = idx1;
            }
        }
        // finish up
        if( idx0 != n-1 ) {
            cs = 0;
            mx = 0;
            for(int i = idx0; i < n; ++i) { // idx1 = n
                cs += cost[i];
                mx = max(mx,cost[i]);
            }
            r += cs-mx;
        }

        return r;
    }
};
