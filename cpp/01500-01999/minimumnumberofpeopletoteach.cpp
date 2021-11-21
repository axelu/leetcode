
// 1733. Minimum Number of People to Teach
// https://leetcode.com/problems/minimum-number-of-people-to-teach/





class Solution {
private:
    int M;

    bool speaksLanguage(int u, int lang, vector<vector<int>>& languages) {
        // TODO remember the answer as it does not change
        return binary_search(languages[u-1].begin(),languages[u-1].end(),lang);
    }

    bool haveCommonLanguage(int u, int v, vector<vector<int>>& languages, int commonLanguage[]) {
        int clidx = u*M+v;
        if( commonLanguage[clidx] != -1 ) return commonLanguage[clidx];

        for(int i = 0; i < languages[u-1].size(); ++i)
            if( speaksLanguage(v,languages[u-1][i],languages) ) {
                commonLanguage[clidx] = 1;
                return true;
            }
        commonLanguage[clidx] = 0;
        return false;
    }
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        M = languages.size(); // number users
        for(int i = 0; i < M; ++i) sort(begin(languages[i]),end(languages[i]));

        // undirected graph with one or more connected components
        vector<int> g[M+1];
        for(int i = 0; i < friendships.size(); ++i) {
            g[friendships[i][0]].push_back(friendships[i][1]);
            g[friendships[i][1]].push_back(friendships[i][0]);
        }

        int ans = M; // worst case, all users must be taught
        int seen[M+1];
        int added[M+1];
        int taught[M+1];
        int commonLanguage[(M+1)*(M*1)]; memset(commonLanguage,-1,sizeof commonLanguage);
        int u,v;
        queue<int> q;
        for(int i = 1; i <= n; ++i) { // for each language

            // BFS level order traversal
            memset(seen,0,sizeof seen);
            memset(added,0,sizeof added);
            memset(taught,0,sizeof taught);
            for(int j = 1; j <= M; ++j) { // for each user
                // TODO optimization: if the answer for a given connected component is 0
                //                    we can skip it in the future
                if( !seen[j] ) {
                    q.push(j);
                    added[j] = 1;
                    while( !q.empty() ) {
                        u = q.front();
                        q.pop();
                        seen[u] = 1;
                        for(int k = 0; k < g[u].size(); ++k) {
                            v = g[u][k];
                            if( seen[v] ) continue;
                            // do u and v speak the same language?
                            if( !haveCommonLanguage(u,v,languages,commonLanguage) ) {
                                // does u speak the current language?
                                if( !speaksLanguage(u,i,languages) ) taught[u] = 1;
                                // does v speak the current language?
                                if( !speaksLanguage(v,i,languages) ) taught[v] = 1;
                            }
                            if( !added[v] ) {
                                q.push(v);
                                added[v] = 1;
                            }
                        }
                    }
                }
            }
            ans = min(ans,accumulate(taught,taught+M+1,0));
            if( ans == 0 ) break;
        }
        return ans;
    }
};
