
// 2127. Maximum Employees to Be Invited to a Meeting
// https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/



class Solution {
private:
    vector<int> chains;

    int inCycle;
    int maxCycle;

    pair<int,int> dfs(vector<int> g[], int u, pair<int,int> seen[]) {
        // cout << "dfs u " << u << endl;

        seen[u] = {-3,-1}; // seen but undetermined

        // we one and only have one outgoing connection!
        int v = g[u][0];

        pair<int,int> p;

        if( seen[v].first == -4 ) {
            // is v pointing us ?
            if( g[v][0] == u ) {
                chains.push_back(1);
                int chainIdu = chains.size()-1;
                seen[u] = {chainIdu,1};
                chains.push_back(1);
                int chainIdv = chains.size()-1;
                seen[v] = {chainIdv,1};
                return {chainIdu,1};
            } else {
                p = dfs(g,v,seen);
            }

        } else if( seen[v].first == -3 ) {
            // cycle
            seen[u] = {-1,1};
            inCycle = v;
            return {-1,1};

        } else if( seen[v].first == -2 || seen[v].first == -1 ) {
            seen[u] = {-2,-1};
            return {-2,-1};

        } else {
            // chain: v is part of a chain
            int chainId = seen[v].first;
            int chainSz = seen[v].second;

            seen[u] = {chainId,chainSz+1};
            chains[chainId] = max(chains[chainId],chainSz+1);
            return {chainId,chainSz+1};
        }

        // after we went deeper
        if( inCycle != -1 ) {
            // am I the end of the cycle
            if( inCycle == u ) {
                inCycle = -1;

                seen[u] = {-1,p.second+1};
                maxCycle = max(maxCycle,p.second+1);
                return {-2,-1};

            } else {

                seen[u] = {-1,p.second+1};
                return {-1,p.second+1};
            }
        } else if( p.first == -2 ) {
            // u is leading to a cycle
            seen[u] = {-2,-1};
            return {-2,-1};
        } else {
            // u is part of a chain
            int chainId = p.first;
            int chainSz = p.second;
            seen[u] = {chainId,chainSz+1};
            chains[chainId] = max(chains[chainId],chainSz+1);
            return {chainId,chainSz+1};
        }

    }

public:
    int maximumInvitations(vector<int>& favorite) {
        // looking at direction i -> favorite[i]
        //
        // each node has exactly 1 outgoing connection ( outdegree = 1 )
        // each node can have 0 to n-1 incoming connections ( indegree )
        // with that we either have a cycle OR
        // if the outgoing connection points to a node that points to us
        // (which terminates a chain), we have a chain, we can combine chains

        // said differently:
        // a node is either part of a cycle ( we can 0 or more cycles in our graph) OR
        // part of a strain that connects to a cycle (but because its outside the cycle
        // would not be part of the solution) OR
        // part of a chain. we can combine chains
        // in case our graph has one or more cycles the answer is either the largest cycle OR
        // in case we have 1 or more chains, we look for the sum of the chains
        // a graph could have zero or more cycles and 0 or more chains
        // if we have a node with an indegree of 0, it either starts a chain or leads to a cycle


        int n = favorite.size();
        int indegree[n];memset(indegree,0,sizeof indegree);
        vector<int> g[n]; // directed graph
        for(int i = 0; i < n; ++i) {
            g[i].push_back(favorite[i]);
            ++indegree[favorite[i]];
        }


        // >= 0 part of chain, size of chain from current node forward
        // -1 node part of a cycle
        // -2 node leads to a cycle
        // -3 seen but undetermined (intermediate state)
        // -4 not seen
        pair<int,int> seen[n];
        for(int i = 0; i < n; ++i)
            seen[i] = {-4,-1};

        inCycle = -1;
        maxCycle = 0;

        // first explore all nodes with indgree 0
        for(int u = 0; u < n; ++u) {
            // if( indegree[u] == 0 ) {
            if( seen[u].first == -4 ) {
                auto p = dfs(g,u,seen);
                /*
                if( inCycle != -1 ) {
                    // am I the end of the cycle
                    if( inCycle == u ) {
                        inCycle = -1;

                        seen[u] = {-1,p.second+1};
                        maxCycle = max(maxCycle,p.second+1);

                    } else {

                        seen[u] = {-1,p.second+1};
                    }
                } else if( p.first == -2 ) {
                    // u is leading to a cycle
                    seen[u] = {-2,-1};
                } else {
                    // u is part of a chain
                    int chainId = p.first;
                    int chainSz = p.second;

                    chains[chainId] = max(chains[chainId],chainSz+1);
                }
                */
            }
        }

        /*
        cout << "maxCycle " << maxCycle << endl;
        for(int l : chains)
            cout << l << " ";
        cout << endl;
        */

        int chainSum = accumulate(chains.begin(),chains.end(),0);
        // cout << "chainSum " << chainSum << endl;

        return max(maxCycle,chainSum);
    }
};
