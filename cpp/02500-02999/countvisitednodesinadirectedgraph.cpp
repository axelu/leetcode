
// 2876. Count Visited Nodes in a Directed Graph
// https://leetcode.com/problems/count-visited-nodes-in-a-directed-graph/



class Solution {
private:
    void dfs(vector<int>& g, int u, int seen[], stack<int>& stck) {
        seen[u] = 1;

        int v = g[u];
        if( !seen[v] )
            dfs(g,v,seen,stck);

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

    vector<int> has_cycle(vector<int>& g, stack<int>& stck, vector<int>& to) {
        // returns nodes involved in a cycle
        vector<int> ret;

        // to will be filled with the nodes in topological order
        unordered_map<int, int> pos;
        int i = 0;
        int n = stck.size();
        while( !stck.empty() ) {
            to.push_back(stck.top());
            pos[stck.top()] = i;
            ++i;
            stck.pop();
        }

        for(int u = 0; u < n; ++u) {
            int v = g[u];
            // if parent vertex does not appear first
            if( pos[u] > pos[v] ) {
                // the we have a cycle exists
                ret.push_back(v);
            }
        }

        return ret;
    }

    int dfs(vector<int>& g, int u, int seen[], vector<int>& ans) {
        if( ans[u] != -1 )
            return ans[u];

        seen[u] = 1;
        return ans[u] = dfs(g,g[u],seen,ans) + 1;
    }

public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();

        // each node in our directed graph has an outdegree of 1 !!!
        // we have no self-edges
        // our graph will have one or more connected components
        // each connected component will have exactly one cycle
        // lets use topological sort to find a node that is part of the cycle
        // then from that node get all the nodes in the cycle and the cycle size
        // then from any node not seen, we do a dfs till we hit a node previously seen,
        // of which the answer then must be the seen node's answer + 1

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[n];memset(seen,0,sizeof seen);
        for(int u = 0; u < n; ++u)
            if( !seen[u] )
                dfs(edges,u,seen,stck);

        vector<int> to; // nodes in topological order
        vector<int> involved = has_cycle(edges,stck,to); // nodes involved in a cycle

        vector<int> ans(n,-1);

        memset(seen,0,sizeof seen); // reset seen
        for(int a: involved) {

            // get the size of the cycle
            stack<int> in_cycle;
            in_cycle.push(a);
            seen[a] = 1;
            int nxt = edges[a];
            int cycle_size = 1;
            while( nxt != a ) {
                ++cycle_size;
                if( seen[nxt] )
                    break;
                seen[nxt] = 1;
                in_cycle.push(nxt);
                nxt = edges[nxt];
            }

            // prefil answer for all nodes in this cycle
            while( !in_cycle.empty() ) {
                ans[in_cycle.top()] = cycle_size;
                in_cycle.pop();
            }
        }

        for(int i = 0; i < n; ++i) {
            int u = to[i];
            if( seen[u] )
                continue;
            dfs(edges,u,seen,ans);
        }

        return ans;
    }
};
