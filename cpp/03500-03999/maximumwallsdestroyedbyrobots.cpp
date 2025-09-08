
// 3661. Maximum Walls Destroyed by Robots
// https://leetcode.com/problems/maximum-walls-destroyed-by-robots/


class Solution {
private:
    int n;
    vector<array<int,3>> robot_index;
    vector<int> prefixSum;

    long long mem[100000][2];

    long long rec(int i, bool pre_right) {
        // pre_left = true means the robot to our left shot right

        if( i == n )
            return 0LL;

        // TODO mem, key pos, pre_right
        if( mem[i][pre_right] != -1LL )
            return mem[i][pre_right];

        // we have a choice
        //      shoot left OR
        //      shoot right

        long long ret = 0LL;

        int idx = robot_index[i][0];
        int lft_reachable_idx = robot_index[i][1];
        int rgt_reachable_idx = robot_index[i][2];
        long long walls_destroyed;

        // shoot left
        if( pre_right ) {
            // we may overlap with the robot to our left, which shot right,
            // hence no double count !!!
            if( i > 0 ) {
                // index that the robot to our left covers when it shoots right
                int lft_robot_rgt_reachable_idx = robot_index[i-1][2];
                lft_reachable_idx = max( lft_robot_rgt_reachable_idx + 1, lft_reachable_idx);
            }
        }
        walls_destroyed = prefixSum[idx] - prefixSum[lft_reachable_idx];
        ret = max(ret, walls_destroyed + rec(i+1, false));

        // shoot right
        walls_destroyed = prefixSum[rgt_reachable_idx+1] - prefixSum[idx];
        ret = max(ret, walls_destroyed + rec(i+1, true));

        return mem[i][pre_right] = ret;
    }

public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        n = robots.size(); // 1 <= robots.length == distance.length <= 1e5

        // 1 <= robots[i], walls[j] <= 1e9
        // All values in robots are unique
        // All values in walls are unique

        // we will sort the robots by position asc
        // we will compress robot and wall coordinates
        // each robot will need to know the position of the next left and right robot
        // as each robot will shoot, for simplification, all walls
        // that share a position with a robot will for sure be destroyed
        // if we would process robots from left to right, the only thing
        // that matters is, if the left robot shot left or right, so
        // our key is pos + left robot shot left or right

        long long base = 0LL; // number of positions shared by robot and wall

        set<int> positions; // unique robot and wall positions
        for(int x: robots)
            positions.insert(x);
        set<int> wall_positions; // unique positions of walls only
        for(int x: walls) {
            bool inserted = positions.insert(x).second;
            if( !inserted )
                ++base;
            else
                wall_positions.insert(x);
        }

        map<int,int> pi; // key: position value: index
        int idx = 0;
        for(int x: positions)
            pi[x] = idx++;

        int pos_sz = idx;
        vector<int> _walls(pos_sz,0);
        for(int x: walls) {
            auto f = wall_positions.find(x);
            if( f != wall_positions.end() )
                _walls[pi[x]] = 1;
        }

        prefixSum.resize(pos_sz+1);
        prefixSum[0] = 0;
        for(int i = 1; i <= pos_sz; ++i)
            prefixSum[i] = prefixSum[i-1] + _walls[i-1];

        // sort robots
        vector<pair<int,int>> _robots(n); // {{pos,distance}, {pos,distance}, ...}
        for(int i = 0; i < n; ++i)
            _robots[i] = {robots[i], distance[i]};
        sort(begin(_robots), end(_robots));


        // translate _robots to indices and left and right reachable index
        robot_index.resize(n); // {{pos index, left reachable index, right reachable index}, ...}
        for(int i = 0; i < n; ++i) {
            int position = _robots[i].first;
            int dist = _robots[i].second;

            int curr_idx = pi[position];

            // left reachable index
            int left = max(1, position - dist);
            int left_idx = pi.lower_bound(left)->second; // will at least find us
            // next robot to our left
            if( i > 0 ) {
                int idx_robot_left = robot_index[i-1][0];
                left_idx = max(left_idx, idx_robot_left+1);
            }

            // right reachable index
            int right = position + dist;
            auto right_it = pi.lower_bound(right);
            if( right_it == pi.end() || right_it->first > right )
                --right_it;
            int right_idx = right_it->second;
            // next robot to our right
            if( i < n-1 ) {
                int pos_robot_right = _robots[i+1].first;
                int idx_robot_right = pi[pos_robot_right];
                right_idx = min(right_idx, idx_robot_right-1);
            }

            robot_index[i] = {curr_idx, left_idx, right_idx};
        }

        memset(mem, -1, sizeof mem);
        return base + rec(0, false);
    }
};
