
// 2097. Valid Arrangement of Pairs
// https://leetcode.com/problems/valid-arrangement-of-pairs/


// see
// https://cp-algorithms.com/graph/euler_path.html
// https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/


// Eulerian path Eulerian cycle Hierholzer algorithm directed graph
class Solution {
private:
    vector<int> findEulerPath(unordered_map<int,vector<int>>& g, int start) {
        vector<int> path;
        
        stack<int> stck;
        stck.push(start);
        int v,u;
        while( !stck.empty() ) {
            u = stck.top();
            if( g[u].size() == 0 ) {
                path.push_back(u);
                stck.pop();
            } else {
                v = g[u].back();
                g[u].pop_back();
                stck.push(v);
            }
        }   
        return path;
    }
    
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        // 1 <= pairs.length <= 10^5
        // 0 <= starti, endi <= 10^9
        // test cases are generated such that there is an Eulerian path
        
        int n = pairs.size();
        if( n == 1 )
            return pairs;
        
        unordered_map<int,int> indegree;
        unordered_map<int,vector<int>> g; // directed graph
        for(auto& p : pairs) {
            g[p[0]].push_back(p[1]);
            ++indegree[p[1]];
        }
        
        /*
        // debug
        cout << "edgelist" << endl;
        for(auto it = g.begin(); it != g.end(); ++it) {
            cout << it->first << ": ";
            for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                cout << *iti << " ";
            }
            cout << endl;
        }
        */
        
        // test cases are generated such that there is an Eulerian path
        // there may or may not be however an Eulerian cycle
        // if there is only an Eulerian path and not an Eularian cycle, 
        // we need to select a node with an odd degree as our starting point
        // our starting node needs to have less incoming than outgoing edges
        int start = g.begin()->first;
        for(auto it = g.begin(); it != g.end(); ++it)
            if( indegree[it->first] < it->second.size() ) {
                start = it->first;
                break;
            }
        
        // cout << "start " << start << endl;
        vector<int> path = findEulerPath(g,start);
        
        /*
        // debug
        for(int i = path.size()-1; i >= 0; --i)
            cout << path[i] << " ";
        cout << endl;
        */
        
        vector<vector<int>> ans;
        // reverse that path and translate it into edges
        for(int i = path.size()-1; i > 0; --i)
            ans.push_back({path[i],path[i-1]});
        
        return ans;
    }
};
