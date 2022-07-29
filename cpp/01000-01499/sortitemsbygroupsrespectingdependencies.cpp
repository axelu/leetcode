
// 1203. Sort Items by Groups Respecting Dependencies
// https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/




class Solution {
private:
    void dfs(vector<int> g[], int u, int seen[], stack<int>& stck) {

        seen[u] = 1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

    bool has_cycle(vector<int> g[], stack<int>& stck, vector<int>& to) {
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
            for(auto v : g[u]) {
                // if parent vertex does not appear first
                if( pos[u] > pos[v] ) {
                    // the we have a cycle exists
                    return true;
                }
            }
        }

        return false;
    }

public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // build two graphs, one for the groups and another for the items
        // topological sort of groups, if there is a cycle, then we have no solution
        // topological sort of items, if there is a cycle, then we have no solution
        //    extract items in topological order into groups buckets
        //    now we have the items in each group bucket in topological order
        //    print out the group buckets in topological order
        // building the graphs:
        //    if both items in same group, it determines ordering inside the group - item graph
        //    if both items in different group, it determines ordereing of the groups - group graph

        // put un-grouped items each in their own group
        for(int i = 0; i < n; ++i)
            if( group[i] == -1 )
                group[i] = m++;

        vector<int> ig[n]; // item graph, directed graph
        vector<int> gg[m]; // group graph, directed graph

        // beforeItems[i] is a list containing all the items that should come before the i-th item
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < beforeItems[i].size(); ++j) {
                int k = beforeItems[i][j];
                // item k should come before item i
                ig[k].push_back(i);
                // with that group of item k should come before group of item i
                int grp_k = group[k];
                int grp_i = group[i];
                if( grp_k != grp_i )
                    gg[grp_k].push_back(grp_i);
            }
        }

        // topological sort of groups
        stack<int> stck; // visited vertices in topological order
        int seen[max(n,m)];memset(seen,0,sizeof seen);
        for(int u = 0; u < m; ++u)
            if( !seen[u] )
                dfs(gg,u,seen,stck);

        vector<int> grp_to; // groups in topological order
        bool grps_have_cycle = has_cycle(gg,stck,grp_to);
        if( grps_have_cycle )
            return {};

        // topological sort of items
        memset(seen,0,sizeof seen);
        for(int u = 0; u < n; ++u)
            if( !seen[u] )
                dfs(ig,u,seen,stck);

        vector<int> itm_to; // items in topological order
        bool itms_have_cycle = has_cycle(ig,stck,itm_to);
        if( itms_have_cycle )
            return {};

        // extract items into group buckets
        vector<int> group_members[m]; // items in topological order per group
        for(int i = 0; i < n; ++i) {
            int itm = itm_to[i];
            group_members[group[itm]].push_back(itm);
        }

        // finalize answer
        vector<int> ans(n);
        int k = 0;
        for(int i = 0; i < m; ++i) {
            int grp = grp_to[i];
            for(int j = 0; j < group_members[grp].size(); ++j)
                ans[k++] = group_members[grp][j];
        }

        return ans;
    }
};
