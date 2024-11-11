


// 3313. Find the Last Marked Nodes in Tree
// https://leetcode.com/problems/find-the-last-marked-nodes-in-tree/

class Solution {
private:
    struct TreeNode {
        bool isLeave;
        array<int,3> furthest;       // dist, subtree, furthest node in that subtree
        array<int,3> secondFurthest; // dist, subtree, furthest node in that subtree
        vector<int> neighbors;
        TreeNode() : isLeave(false), furthest({-1,-1,-1}), secondFurthest({-1,-1,-1}), neighbors({}) {}
    };
    
    pair<int,int> dfs(TreeNode* t[], int u, int src) {
        // cout << "dfs u " << u << " src " << src << endl;
        // returns distance to furthest node, and the node id of that node,
        // in any subtree other than the subtree in src
        
        if( src != -1 && t[u]->isLeave )
            return {1, u};
        
        for(auto it = t[u]->neighbors.begin(); it != t[u]->neighbors.end(); ) {
            int v = *it;
            // cout << "  v " << v << endl;
            if( v == src ) {
                ++it;
                continue;
            }
            
            auto p = dfs(t, v, u);
            
            if( p.first > t[u]->furthest[0] ) {
                // push furthest to secondFurthest
                t[u]->secondFurthest = t[u]->furthest;

                t[u]->furthest[0] = p.first;
                t[u]->furthest[1] = v;
                t[u]->furthest[2] = p.second;
                
            } else if( p.first > t[u]->secondFurthest[0] ) { 
                t[u]->secondFurthest[0] = p.first;
                t[u]->secondFurthest[1] = v;
                t[u]->secondFurthest[2] = p.second;
            }
            
            it = t[u]->neighbors.erase(it);
        }
        
        if( t[u]->furthest[1] != src ) {
            // cout << "dfs u " << u << " src " << src << " result " << "{" << t[u]->furthest[0]+1 << "," << t[u]->furthest[2] << "}" << endl;
            return {t[u]->furthest[0]+1,t[u]->furthest[2]};
        } else {
            // cout << "dfs u " << u << " src " << src << " result " << "{" << t[u]->secondFurthest[0]+1 << "," << t[u]->secondFurthest[2] << "}" << endl;
            return {t[u]->secondFurthest[0]+1,t[u]->secondFurthest[2]};
        }
    }
    
public:
    vector<int> lastMarkedNodes(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        
        TreeNode* t[n];
        for(int i = 0; i < n; ++i)
            t[i] = new TreeNode();
        
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];            
            t[u]->neighbors.push_back(v);
            t[v]->neighbors.push_back(u);
        }
        
        // mark leaves
        for(int i = 0; i < n; ++i)
            if( t[i]->neighbors.size() == 1 )
                t[i]->isLeave = true;
        
        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = dfs(t,i,-1).second;
        
        return ans;
    }
};




// passes 765/767 test cases, then TLE as of 10/8/2024

class Solution {
private:
    struct TreeNode {
        // TODO we only need to keep furthest node and second furthest node
        vector<int> neighbors;
        vector<int> mxdist;
        vector<int> mxnode;
        TreeNode() : neighbors({}), mxdist({}), mxnode({}) {}
    };

    pair<int,int> dfs(TreeNode* t[], int u, int src) {
        // cout << "dfs u " << u << " src " << src << endl;
        // returns distance to furthest node, and the node id of that node,
        // in any subtree other than the subtree in src


        int ret_dist = 1;
        int ret_node = u;
        if( src == -1 ) {
            ret_dist = 0;
        }

        auto itdist = t[u]->mxdist.begin();
        auto itnode = t[u]->mxnode.begin();
        for(auto it = t[u]->neighbors.begin(); it != t[u]->neighbors.end(); ++it) {
            int v = *it;
            // cout << "  v " << v << endl;
            if( v == src ) {
                ++itdist;
                ++itnode;
                continue;
            }

            if( *itdist == -1 ) {
                auto p = dfs(t, v, u);
                *itdist = p.first;
                *itnode = p.second;
            }

            if( *itdist + 1 > ret_dist ) {
                ret_dist = *itdist + 1;
                ret_node = *itnode;
            }

            ++itdist;
            ++itnode;
        }

        // cout << "dfs u " << u << " src " << src << " result " << "{" << ret_dist << "," << ret_node << "}" << endl;
        return {ret_dist, ret_node};
    }

public:
    vector<int> lastMarkedNodes(vector<vector<int>>& edges) {
        int n = edges.size() + 1;

        TreeNode* t[n];
        for(int i = 0; i < n; ++i)
            t[i] = new TreeNode();

        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];

            t[u]->neighbors.push_back(v);
            t[u]->mxdist.push_back(-1);
            t[u]->mxnode.push_back(-1);

            t[v]->neighbors.push_back(u);
            t[v]->mxdist.push_back(-1);
            t[v]->mxnode.push_back(-1);
        }

        vector<int> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = dfs(t,i,-1).second;

        return ans;
    }
};

