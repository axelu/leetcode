
// 1263. Minimum Moves to Move a Box to Their Target Location
// https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/




class Solution {
private:
    struct T {
        int pushes;
        int player_row;
        int player_col;
        int box_row;
        int box_col;
        T(int p, int pr, int pc, int br, int bc) : pushes(p), player_row(pr), player_col(pc), box_row(br), box_col(bc) {}
    };

    int hash(T& t) {
        int ret = 0 + (t.player_row<<15) + (t.player_col<<10) + (t.box_row<<5) + t.box_col;
        return ret;
    }

public:
    int minPushBox(vector<vector<char>>& grid) {
        // get position of box and player
        int m = grid.size();
        int n = grid[0].size();

        // it is garanteed that there is exactly one player, box and target
        int player_row, player_col;
        int box_row, box_col;
        int target_row, target_col;

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 'B' ) {
                    box_row = i;
                    box_col = j;
                } else if( grid[i][j] == 'S' ) {
                    player_row = i;
                    player_col = j;
                } else if( grid[i][j] == 'T' ) {
                    target_row = i;
                    target_col = j;
                }
            }

        // BFS
        // directions  R  D  L  U
        int dirR[] = { 0, 1, 0,-1};
        int dirC[] = { 1, 0,-1, 0};

        auto cmp = [](const T& a, const T& b) {
            return a.pushes > b.pushes;
        };
        priority_queue<T,vector<T>,decltype(cmp)> pq(cmp);
        unordered_set<int> seen;
        T t = {0,player_row,player_col,box_row,box_col};
        pq.push(t);
        seen.insert(hash(t));
        while( !pq.empty() ) {
            t = pq.top();
            pq.pop();

            if( t.box_row == target_row && t.box_col == target_col )
                return t.pushes;

            // explore all four directions
            // try to move our player
            for(int k = 0; k < 4; ++k) {
                box_row = t.box_row;
                box_col = t.box_col;

                int player_row_new = t.player_row + dirR[k];
                if( player_row_new < 0 || player_row_new == m )
                    continue;

                int player_col_new = t.player_col + dirC[k];
                if( player_col_new < 0 || player_col_new == n )
                    continue;

                // is it a wall?
                if( grid[player_row_new][player_col_new] == '#' )
                    continue;

                // did we step onto the box?  if so, could we push it?
                if( player_row_new == t.box_row && player_col_new == t.box_col ) {
                    bool can_push_box = true;

                    box_row += dirR[k];
                    if( box_row < 0 || box_row == m )
                        can_push_box = false;

                    if( can_push_box ) {
                        box_col += dirC[k];
                        if( box_col < 0 || box_col == n )
                            can_push_box = false;
                    }

                    if( can_push_box ) {
                        if( grid[box_row][box_col] == '#' )
                            can_push_box = false;
                    }

                    if( can_push_box ) {
                        T t_new = {t.pushes+1,player_row_new,player_col_new,box_row,box_col};
                        int h = hash(t_new);
                        if( !seen.count(h) ) {
                            seen.insert(h);
                            pq.push(t_new);
                        }
                    }
                } else {
                        T t_new = {t.pushes,player_row_new,player_col_new,box_row,box_col};
                        int h = hash(t_new);
                        if( !seen.count(h) ) {
                            seen.insert(h);
                            pq.push(t_new);
                        }
                }
            }
        }

        return -1;
    }
};
