
// 433. Minimum Genetic Mutation
// https://leetcode.com/problems/minimum-genetic-mutation/



class Solution {
private:
    int diff_cnt(string a, string b) {
        // a.size() == b.size() == 8
        // returns true if there is 1 char diff between a and b
        // otherwise false
        int diff_cnt = 0;
        for(int i = 0; i < 8; ++i)
            if( a[i] != b[i] )
                ++diff_cnt;

        return diff_cnt;
    }

public:
    int minMutation(string start, string end, vector<string>& bank) {
        // start is assumed to be valid, but it might not be included in the bank
        if( bank.empty() )
            return -1;

        // bank may have duplicates, so remove duplicates
        for(auto it = next(bank.begin()); it != bank.end(); )
            if( *prev(it) == *it )
                it = bank.erase(it);
            else
                ++it;

        int n = bank.size();
        if( n == 0 ) // end has to be in the bank
            return -1;

        // build an undirected graph
        vector<vector<int>> g(n);
        int s = -1;
        int e = -1;
        vector<int> start_mutations;
        for(int i = 0; i < n; ++i) {

            if( bank[i] == start )
                s = i;
            else {
                if( bank[i] == end )
                    e = i;
                if( diff_cnt(start,bank[i]) == 1 )
                    start_mutations.push_back(i);
            }

            for(int j = i+1; j < n; ++j)
                if( diff_cnt(bank[i],bank[j]) == 1 ) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
        }

        if( e == -1 ) // end has to be in the bank
            return -1;
         if( start_mutations.empty() ) // no mutations of start
            return -1;

        if( s == -1 ) {
            // we need to add start into our graph
            // in order to do so, we need to have mutations of start
            for(int u : start_mutations)
                g[u].push_back(n);

            g.push_back(start_mutations);
            s = n;
        }

        // BFS
        queue<int> q;
        int seen[g.size()];memset(seen,0,sizeof seen);
        q.push(s);
        seen[s] = 1;

        int step = 0;
        while( !q.empty() ) {

            queue<int> q_new;
            while( !q.empty() ) {
                int u = q.front();
                q.pop();

                if( u == e )
                    return step;

                for(int i = 0; i < g[u].size(); ++i) {
                    int v = g[u][i];
                    if( seen[v] )
                        continue;
                    seen[v] = 1;
                    q_new.push(v);
                }
            }
            ++step;
            q = q_new;
        }

        return -1;
    }
};
