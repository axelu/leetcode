
// 1377. Frog Position After T Seconds
// https://leetcode.com/problems/frog-position-after-t-seconds/





class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if( n == 1 )
            return 1.0;

        vector<int> G[n+1];
        for(int i = 0; i < edges.size(); ++i) {
            G[edges[i][0]].push_back(edges[i][1]);
            G[edges[i][1]].push_back(edges[i][0]);
        }

        // BFS

        struct T{
            int node;
            int step;
            double probability;
        };

        int seen[n+1];memset(seen,0,sizeof seen);

        queue<T> q;
        q.push({1,0,1.0});
        seen[1] = 1;

        int u,step,v,divisor,k;
        double probability,probability_new;
        while( !q.empty() ) {
            u = q.front().node;
            step = q.front().step;
            probability = q.front().probability;
            q.pop();

            // cout << "node " << u << " step " << step << " probability " << probability;
            // cout << " edges " << G[u].size() << endl;

            // the time has passed
            // but we have not reached the target
            if( step == t )
                return 0.0;


            // we need to discount the edges from
            // u to nodes we have already seen
            divisor = G[u].size();
            for(k = 0; k < G[u].size(); ++k) {
                v = G[u][k];
                if( seen[v] )
                    --divisor;
            }
            if( divisor == 0 )
                continue;
            probability_new = probability / divisor;

            for(k = 0; k < G[u].size(); ++k) {
                v = G[u][k];

                if( seen[v] )
                    continue;

                if( v == target ) {
                    // we have reached the target
                    // it we have reached target before the time
                    // only if the frog is stuck here,
                    // we return the current probability
                    if( step+1 == t || G[v].size() == 1 )
                        return probability_new;
                    else {
                        return 0.0;
                    }
                }

                seen[v] = 1;

                q.push({v,step+1,probability_new});
            }
        }

        if( step < t )
            return 0.0;
        return -1.0; // satisfy compiler
    }
};
