
// 2307. Check for Contradictions in Equations
// https://leetcode.com/problems/check-for-contradictions-in-equations/


class Solution {
private:
    bool dfs(unordered_map<string,vector<pair<string,double>>>& g,
             string u,
             double value,
             unordered_map<string,double>& seen) {

        // returns true if there is a contradiction

        auto f = seen.find(u);
        if( f != seen.end() )
            return f->second - value >= 1e-5; // floating point compare

        seen[u] = value;

        for(auto it = g[u].begin(); it != g[u].end(); ++it)
            if( dfs(g,(*it).first,value/(*it).second,seen) )
                return true;

        return false;
    }

public:
    bool checkContradictions(vector<vector<string>>& equations, vector<double>& values) {
        // let us build a graph
        // each variable is an node, each 'equation' is an edge.
        // equations[i] = [Ai, Bi] and values[i] means that Ai / Bi = values[i]
        // what "each 'equation' is an edge" means is, that we will put the result of the
        // equation Ai / Bi on the edge.

        // Test Case 68 didn't work unless the dfs is initiated in the order
        // of the nodes discovered in equations,
        // c++ unordered_map doesn't garuantee insertion order, hence
        // using a vector

        unordered_map<string,vector<pair<string,double>>> g; // bidirectional graph
        vector<string> v; // preserve insertion order of nodes for later iteration
        for(int i = 0; i < equations.size(); ++i) { // equations.size == values.size
            string A = equations[i][0];
            string B = equations[i][1];
            double result = values[i];

            // edge A -> B
            if( !g.count(A) )
                v.push_back(A);
            g[A].push_back({B,result});
            // edge B -> A
            if( !g.count(B) )
                v.push_back(B);
            g[B].push_back({A,1.0/result});

        }

        // we assign an arbitrary value (let us say 1.0) to an unseen node, which means
        // we assign that value to the variable and start a DFS
        // and we execute the 'equations' by walking the graph, the result of a calculation
        // must be the value of the node that the edge is pointing to
        // in 'seen' we will capture the value we assigned or calculated to a given node
        unordered_map<string,double> seen;
        for(auto& u : v)
            if( !seen.count(u) && dfs(g,u,1.0,seen) )
                return true;

        return false; // return false if there is NO contradiction
    }
};
