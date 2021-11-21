
// 1055. Shortest Way to Form String
// https://leetcode.com/problems/shortest-way-to-form-string/





class Solution {
public:
    int shortestWay(string source, string target) {
        int n = source.size();

        set<int> pos[26];
        for(int i = 0; i < n; ++i)
            pos[source[i]-'a'].insert(i);



        int m = target.size();
        int dp[m];


        for(int i = m-1; i >= 0; --i) {
            int charIdx = target[i]-'a';
            if( pos[charIdx].size() == 0 )
                    return -1;

            int t = INT_MAX;
            // start at every position in source that has the current target char
            for(auto it = pos[charIdx].begin(); it != pos[charIdx].end(); ++it) {
                int posInSource = *it;

                int j = i+1;
                for(; j < m; ++j) {

                    auto ub = pos[target[j]-'a'].upper_bound(posInSource);
                    if( ub != pos[target[j]-'a'].end() ) {
                        posInSource = *ub;
                    } else {
                        break;
                    }
                }
                if( j == m ) {
                    t = 1;
                    break;
                } else {
                    t = min(t,1+dp[j]);
                }
            }
            dp[i] = t;
        }


        return dp[0];
    }
};
