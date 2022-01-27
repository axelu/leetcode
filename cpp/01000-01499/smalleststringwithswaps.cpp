
// 1202. Smallest String With Swaps
// https://leetcode.com/problems/smallest-string-with-swaps/




class Solution {
private:
    void bfs(string& s, int i, vector<int> g[], int seen[]) {
        seen[i] = 1;

        queue<int> q;
        q.push(i);
        set<int> indicies; // ordered indicies
        indicies.insert(i);
        int cnt[26];memset(cnt,0,sizeof cnt);
        ++cnt[s[i]-'a'];
        int u,v;
        while( !q.empty() ) {
            u = q.front();
            q.pop();

            for(int k = 0; k < g[u].size(); ++k) {
                v = g[u][k];
                if( seen[v] )
                    continue;

                seen[v] = 1;
                indicies.insert(v);
                ++cnt[s[v]-'a'];
                q.push(v);
            }
        }
        // apply
        int j = 0;
        for(auto it = indicies.begin(); it != indicies.end(); ++it) {
            while( cnt[j] == 0 )
                ++j;
            s[*it] = j+'a';
            --cnt[j];
        }

    }
public:
    string smallestStringWithSwaps(string& s, vector<vector<int>>& pairs) {
        int n = s.size();
        if( n == 1 )
            return s;

        int psz = pairs.size();
        if( psz == 0 )
            return s;

        // pairs are connected nodes in a graph
        // will assume pairs are unique and pairs[i] = [a,b] -> a != b;
        vector<int> g[n];
        for(int i = 0; i < psz; ++i) {
            g[pairs[i][0]].push_back(pairs[i][1]);
            g[pairs[i][1]].push_back(pairs[i][0]);
        }

        // we have connected components
        // the chars in each can be sorted and
        // applied to the indicies sorted

        // collect all chars in the connected component
        // collect all indicies in the connected component
        // apply sorted chars to indicies
        int seen[n];memset(seen,0,sizeof seen);
        for(int i = 0; i < n; ++i)
            if( !seen[i] )
                bfs(s,i,g,seen);

        return s;
    }
};
