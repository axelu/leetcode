
// 943. Find the Shortest Superstring
// https://leetcode.com/problems/find-the-shortest-superstring/
// day 23 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3753/



// solution approach #1
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();

        int overlaps[n][n];
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int m = min(words[i].size(),words[j].size());
                for(int k = m; k >= 0; --k) {
                    if( words[i].substr(words[i].size()-k) == words[j].substr(0,k) ) {
                        overlaps[i][j] = k;
                        break;
                    }
                }
            }
        }

        // dp[mask][i] = most overlap with mask, ending with ith element
        int dp[1<<n][n];memset(dp,0,sizeof dp);
        int parent[1<<n][n];memset(parent,-1,sizeof parent);

        for(int mask = 0; mask < (1<<n); ++mask) {
            for(int bit = 0; bit < n; ++bit) {
                if( ((mask>>bit)&1) > 0 ) {
                    int pmask = mask^(1<<bit);
                    if( pmask == 0 ) continue;
                    for(int i = 0; i < n; ++i) {
                        if( ((pmask>>i)&1) > 0 ) {
                            int val = dp[pmask][i] + overlaps[i][bit];
                            if( val > dp[mask][bit] ) {
                                dp[mask][bit] = val;
                                parent[mask][bit] = i;
                            }
                        }
                    }
                }
            }
        }

        vector<int> perm;
        int seen[n];memset(seen,0,sizeof seen);
        int mask = (1<<n) - 1;

        int p = 0;
        for(int i = 0; i < n; ++i) {
            if( dp[(1<<n) - 1][i] > dp[(1<<n) - 1][p] ) {
                p = i;
            }
        }

        while(p != -1) {
            perm.push_back(p);
            seen[p] = 1;
            int p2 = parent[mask][p];
            mask ^= (1<<p);
            p = p2;
        }

        reverse(perm.begin(),perm.end());

        for(int i = 0; i < n; ++i) {
            if( !seen[i] ) {
                perm.push_back(i);
            }
        }

        string ans = words[perm[0]];
        for(int i = 1; i < n; ++i) {
            int overlap = overlaps[perm[i - 1]][perm[i]];
            ans += words[perm[i]].substr(overlap);
        }

        return ans;
    }
};
