
// 3607. Power Grid Maintenance
// https://leetcode.com/problems/power-grid-maintenance/



class Solution {
private:
    vector<int> station2gridid;

    // key: gridid value: operational stations in that grid
    unordered_map<int, set<int>> operationalstationsingrid;

    vector<vector<int>> g;

    void dfs(int u, int gridid) {
        station2gridid[u] = gridid;
        operationalstationsingrid[gridid].insert(u);

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( station2gridid[v] != -1 )
                continue;
            dfs(v, gridid);
        }

        return;
    }

public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        // undirected graph
        g.resize(c+1);
        for(auto& connection: connections) {
            int u = connection[0];
            int v = connection[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // we will assign each station to a power grid that it is part of
        station2gridid.assign(c+1, -1);

        int gridid = 0;
        for(int i = 1; i <= c; ++i) {
            if( station2gridid[i] == -1 ) {
                dfs(i, gridid);
                ++gridid;
            };
        }

        // process queries
        vector<int> ans;
        vector<bool> online(c+1, true); // Initially, all stations are online
        int q_sz = queries.size();
        for(int i = 0; i < q_sz; ++i) {
            int station_id = queries[i][1];
            if( queries[i][0] == 1 ) {
                if( online[station_id] ) {
                    ans.push_back(station_id);
                } else {
                    gridid = station2gridid[station_id];
                    if( operationalstationsingrid[gridid].empty() ) {
                        ans.push_back(-1);
                    } else {
                        ans.push_back(*(operationalstationsingrid[gridid].begin()));
                    }
                }

            } else {
                // a station goes offline
                if( online[station_id] ) {
                    online[station_id] = false;
                    gridid = station2gridid[station_id];
                    operationalstationsingrid[gridid].erase(station_id);
                }
            }
        }

        return ans;
    }
};
