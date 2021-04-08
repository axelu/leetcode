
// 685. Redundant Connection II
// https://leetcode.com/problems/redundant-connection-ii/


class Solution {
private:
    bool dfs(int root, int& dest, pair<vector<int>,vector<int>> t[], int seen[]) {
        // dest  = parent1
        if( root == dest ) return true;
        if( seen[root] ) return false;
        seen[root] = 1;

        for(int i = 0; i < t[root].second.size(); ++i)
            if( dfs(t[root].second[i],dest,t,seen) ) return true;

        return false;
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // observation/idea:
        // case 1: we have a node with no parent, which is the root of our tree
        //         and we have a node with 2 parents,
        //         one of the edges to the node with 2 parents has to go:
        // case 2: each node has 1 parent, so we don't know which node could be the root
        //         answer is the 1st edge from the back of edges, where the child is not
        //         a leaf

        size_t n = edges.size();
        pair<vector<int>,vector<int>> t[n+1]; // parent(s),children(if any);
        int seen[n+1];
        int u; // parent
        int v; // child
        int i;
        int nodeWithTwoParents = -1;
        for(i = 0; i < n; ++i) {
            u = edges[i][0];
            v = edges[i][1];
            // add child to parent
            t[u].second.push_back(v);
            // add parent to child
            t[v].first.push_back(u);
            // does v have more than one parent?
            if( t[v].first.size() != 1 ) nodeWithTwoParents = v; // case 1
        }
        // case 1
        if( nodeWithTwoParents != -1 ) {
            int parent1 = t[nodeWithTwoParents].first[0];
            int parent2 = t[nodeWithTwoParents].first[1];
            // we can eleminate the edge parent2->nodeWithTwoParents if and only if
            // parent1 is not in the subtree of nodeWithTwoParents
            memset(seen,0,sizeof seen);
            if( !dfs(nodeWithTwoParents,parent1,t,seen) )
                return {parent2,nodeWithTwoParents};
            else
                return {parent1,nodeWithTwoParents};
        }
        // case 2
        for(i = n-1; i >= 0; --i) {
            u = edges[i][0];
            v = edges[i][1];
            if( t[v].second.size() == 0 ) continue;
            memset(seen,0,sizeof seen);
            if( dfs(v,u,t,seen) ) break;
        }
        return edges[i];
    }
};
