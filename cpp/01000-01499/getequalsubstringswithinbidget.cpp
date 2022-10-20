
// 1208. Get Equal Substrings Within Budget
// https://leetcode.com/problems/get-equal-substrings-within-budget/




class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int n = s.size(); // s.size = t.size

        int cost[n];
        for(int i = 0; i < n; ++i)
            cost[i] = abs(s[i]-t[i]);

        int ans = 0;

        // sliding window
        int i = 0;  // left index
        int j = 0;  // right index
        int sum = 0;
        int l;      // lenght of sliding window
        for(; j < n; ++j) {
            sum += cost[j];
            if( sum > maxCost) {
                l = j - i;
                ans = max(ans,l);
                while( sum > maxCost && i <= j)
                    sum -= cost[i++];
            }
        }
        if( sum <= maxCost ) {
            l = j - i;
            ans = max(ans,l);
        }

        return ans;
    }
};
