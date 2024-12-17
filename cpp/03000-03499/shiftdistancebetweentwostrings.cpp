
// 3361. Shift Distance Between Two Strings
// https://leetcode.com/problems/shift-distance-between-two-strings/




class Solution {
public:
    long long shiftDistance(string s, string t, vector<int>& nextCost, vector<int>& previousCost) {
        int n = s.size(); // s.size() == t.size()

        long long prefixSum_nxt[27];
        prefixSum_nxt[0] = 0LL;
        for(int i = 1; i <= 26; ++i)
            prefixSum_nxt[i] = prefixSum_nxt[i-1] + (long long)nextCost[i-1];

        long long prefixSum_prev[27];
        prefixSum_prev[0] = 0LL;
        for(int i = 1; i <= 26; ++i)
            prefixSum_prev[i] = prefixSum_prev[i-1] + (long long)previousCost[i-1];

        long long ans = 0LL;

        for(int i = 0; i < n; ++i) {
            if( s[i] == t[i] )
                continue;

            // we either go forward aka nextCost OR
            // we go backward aka previousCost
            // we do whatever is cheaper

            int cs = s[i] - 'a';
            int ct = t[i] - 'a';

            // forward
            long long cost_going_right = LLONG_MAX;
            if( cs < ct ) {
                // no wrap
                cost_going_right = prefixSum_nxt[ct] - prefixSum_nxt[cs];

            } else {
                // wrap
                // go from cs to z
                // go from z to a
                cost_going_right = prefixSum_nxt[26] - prefixSum_nxt[cs];
                // go from a to ct
                cost_going_right += prefixSum_nxt[ct];
            }


            // backward
            long long cost_going_left = LLONG_MAX;
            if( ct < cs ) {
                // no wrap
                cost_going_left = prefixSum_prev[cs+1] - prefixSum_prev[ct+1];

            } else {
                // wrap
                // cost cs to a
                // cost a to z
                cost_going_left = prefixSum_prev[cs+1];
                // cost z to ct
                cost_going_left += prefixSum_prev[26] - prefixSum_prev[ct+1];
            }

            ans += min(cost_going_right, cost_going_left);
        }

        return ans;
    }
};
