
// 3786. Total Sum of Interaction Cost in Tree Groups
// https://leetcode.com/problems/total-sum-of-interaction-cost-in-tree-groups/

class Solution {
private:
    int nbr_groups;
    long long ans;

    struct T {
        long long children;
        long long cost;
        T(): children(0), cost(0) {}
    };

    vector<T> dfs(vector<vector<int>>& t, vector<int>& group, int u, int src, int depth) {
        // returns first:  nbr of nodes in our subtree incl. us per group
        //         second: cost it took children to get to us per group

        // each node will figure out its interaction costs with
        //    all nodes in its subtree of the same group (and record that)
        // each node will figure out the interaction costs
        //    amongst its children
        // each node will commmunicate upwards so that its parent
        //    can do the same

        long long ret = 0;
        int u_grp_idx = group[u];

        vector<T> total(nbr_groups); // TODO don't use vector of fixed length,
                                     // use unordered_map<int,T> instead, so we
                                     // only have to loop over what is found
        for(int v: t[u] ) {
            if( v == src )
                continue;

            auto local = dfs(t, group, v, u, depth+1);
            long long sum = 0;

            for(int i = 0; i < nbr_groups; ++i) { // for each group
                long long children_cnt  = local[i].children;
                if( children_cnt == 0 )
                    continue;

                long long children_cost = local[i].cost; // cost of children of v to visit v

                // interaction cost of our node u with these new children
                // dist from us to v is 1
                long long dist = 1;
                long long cost = (children_cnt * dist) + children_cost;
                if( i == u_grp_idx ) // if same group
                    sum += cost;     // record

                // interaction cost of these new children with already known children
                // so far we have total_children
                // it takes our new children cost to visit us
                // they need to visit us total_children times
                // and it takes our existing children total_cost to come to us
                sum += (total[i].children * cost) + (children_cnt * total[i].cost);

                total[i].cost += cost;
                total[i].children += children_cnt;
            }
            ret += sum;
            // debug
            /*
            if( u == 0 ) {
                cout << "u " << u << " after visiting v " << v << " sum " << sum << " ret " << ret << endl;
            }
            */

        }

        ++total[u_grp_idx].children; // +1 to count us
        // debug
        /*
        cout << "dfs u " << u << " src " << src << endl;
        for(int i = 0; i < nbr_groups; ++i)
            cout << "    grp " << i << " children " << total[i].children << " cost " << total[i].cost << endl;
        */
        ans += ret;
        // cout << "    ans " << ans << endl;

        return total;
    }

public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        // edges.size() == n-1; group.size() == n
        // 1 <= group[i] <= 20

        // reindex groups
        int grp_idx = 0;
        unordered_map<int,int> grps; // key: original group : value: new group
        for(int i = 0; i < n; ++i) {
            int org_grp_idx = group[i];
            auto p = grps.insert({org_grp_idx, grp_idx});
            group[i] = grps[group[i]];
            if( p.second )
                ++grp_idx;
        }
        nbr_groups = grp_idx;

        ans = 0;

        vector<vector<int>> t(n, vector<int>()); // our original undirected tree
        for(int i = 0; i < n-1; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        dfs(t, group, 0, -1 , 0);

        return ans;
    }
};
