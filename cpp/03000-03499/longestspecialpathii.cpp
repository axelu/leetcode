
// 3486. Longest Special Path II
// https://leetcode.com/problems/longest-special-path-ii/










// see 3425. Longest Special Path https://leetcode.com/problems/longest-special-path/

class Solution {
private:
    vector<vector<int>> t[50000];
    int A[50000]; // distance from 0 to node i
    vector<int> path;
    vector<int> last_seen_by_value[50001];

    vector<int> unique_path_start_node;
    vector<int> unique_path_start_step;

    int mx_length_special_path;
    int mn_number_nodes_in_longest_special_path;

    vector<pair<int,int>> offending_pair_step;

    void dfs(vector<int>& nums, int u, int src, int distance, int step) {
        // distance is the distance from root (node 0) to u
        A[u] = distance;
        // record our path
        path.push_back(u);

        int val_u = nums[u];
        // cout << "dfs u " << u << " src " << src << " distance " << distance << " step " << step << " val_u " << val_u << endl;
        bool unique_path_start_backtrack = false;
        bool added_offending_pair = false;
        if( u == 0 ) {
            unique_path_start_backtrack = true;
            unique_path_start_node.push_back(0);
            unique_path_start_step.push_back(0);

        } else {
            int start_of_unique_path_node = unique_path_start_node.back();
            int start_of_unique_path_step = unique_path_start_step.back();

            // have we seen this value in our path before?
            // if so, at what step have we seen it last?
            if( !last_seen_by_value[val_u].empty() ) {
                int step_seen = last_seen_by_value[val_u].back();

                if( step_seen >= start_of_unique_path_step ) {
                    // it is ok to have to have 2 nodes of the same value
                    // in our special path, but there can only be one pair
                    // hence we need to check if there is already a pair of nodes
                    // with the same value in our path
                    // Note: there could already be two of our value also.

                    if( !offending_pair_step.empty() && start_of_unique_path_step <= offending_pair_step.back().first ) {
                        // we need to move our start
                        // but only to the best possible step

                        if( offending_pair_step.back().first < step_seen ) {
                            // our current 'pair' will be the latest offending pair
                            start_of_unique_path_step = offending_pair_step.back().first + 1;
                        } else {
                            // we are moving start beyond last seen
                            start_of_unique_path_step = step_seen + 1;
                        }

                        start_of_unique_path_node = path[start_of_unique_path_step];
                        unique_path_start_backtrack = true;
                        unique_path_start_node.push_back(start_of_unique_path_node);
                        unique_path_start_step.push_back(start_of_unique_path_step);
                    }
                    // depending on the new start, add us as an offending pair or not
                    if( step_seen >= start_of_unique_path_step ) {
                        offending_pair_step.push_back({step_seen, step});
                        added_offending_pair = true;
                    }
                }
            }

            // cout << "a unique path is from node " << start_of_unique_path_node << " at step " << start_of_unique_path_node << " to us" << endl;
            int distance_root_to_start_of_unique_path = A[start_of_unique_path_node];
            int distance_start_of_unique_path_to_u = distance - distance_root_to_start_of_unique_path;
            if( distance_start_of_unique_path_to_u > mx_length_special_path ) {
                mx_length_special_path = distance_start_of_unique_path_to_u;
                mn_number_nodes_in_longest_special_path = step - start_of_unique_path_step + 1;
            } else if( distance_start_of_unique_path_to_u == mx_length_special_path ) {
                if( mn_number_nodes_in_longest_special_path > step - start_of_unique_path_step + 1 )
                    mn_number_nodes_in_longest_special_path = step - start_of_unique_path_step + 1;
            }
        }
        // record that val_u was seen at step
        last_seen_by_value[val_u].push_back(step);

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i][0];
            if( v == src )
                continue;

            int length = t[u][i][1];

            dfs(nums, v, u, distance + length, step + 1);
        }

        // backtrack
        path.pop_back();
        last_seen_by_value[val_u].pop_back();
        if( unique_path_start_backtrack ) {
            unique_path_start_node.pop_back();
            unique_path_start_step.pop_back();
        }
        if( added_offending_pair )
            offending_pair_step.pop_back();

        return;
    }

public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        // undirected tree rooted at node 0, with n nodes
        // edges[i] = [ui, vi, lengthi]
        // int n = edges.size() + 1; // 2 <= n <= 5 * 1e4


        // even if two adjacent nodes have the same value, that would be a valid
        // special path, so at minimum we have two nodes in a special path (2 <= n also)
        // and our minimum length of a special path is our longest edge
        mx_length_special_path = 0;
        mn_number_nodes_in_longest_special_path = 2;

        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int length = edge[2];
            t[u].push_back({v,length});
            t[v].push_back({u,length});

            mx_length_special_path = max(mx_length_special_path, length);
        }

        // the tree is rooted in 0
        A[0] = 0;
        dfs(nums, 0, -1, 0, 0);

        return {mx_length_special_path, mn_number_nodes_in_longest_special_path};
    }
};
