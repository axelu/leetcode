
// 1728. Cat and Mouse II
// https://leetcode.com/problems/cat-and-mouse-ii/



class Solution {
private:
    int m,n;
    int row_food,col_food;

    int can_reach_food(vector<string>& grid, int i, int j, int jumps,
                       int A[], vector<int> g[]) {
        // cout << "can_reach_food i " << i << " j " << j;
        // cout << " jumps " << jumps << endl;

        // return min nbr turns to go from [i,j] to [row_food,col_food]
        // regardless of cat position
        // build a graph along the way and record the shortest path
        // from start to every point in the graph

        // BFS
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[2] > b[2];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        pq.push({i,j,0});
        A[i * n + j] = 0;
        while( !pq.empty() ) {
            i = pq.top()[0];
            j = pq.top()[1];
            int u = i * n + j;
            int turns = pq.top()[2];
            pq.pop();

            // explore all four directions
            // right
            for(int k = 1; k <= jumps; ++k) {
                int j_new = j + k;
                if( j_new == n || grid[i][j_new] == '#' )
                    break;
                int v = i * n + j_new;
                g[u].push_back(v);
                if( A[v] == 1001 ) {
                    A[v] = turns+1;
                    pq.push({i,j_new,turns+1});
                }
            }
            // down
            for(int k = 1; k <= jumps; ++k) {
                int i_new = i + k;
                if( i_new == m || grid[i_new][j] == '#' )
                    break;
                int v = i_new * n + j;
                g[u].push_back(v);
                if( A[v] == 1001 ) {
                    A[v] = turns+1;
                    pq.push({i_new,j,turns+1});
                }
            }
            // left
            for(int k = 1; k <= jumps; ++k) {
                int j_new = j - k;
                if( j_new < 0 || grid[i][j_new] == '#' )
                    break;
                int v = i * n + j_new;
                g[u].push_back(v);
                if( A[v] == 1001 ) {
                    A[v] = turns+1;
                    pq.push({i,j_new,turns+1});
                }
            }
            // up
            for(int k = 1; k <= jumps; ++k) {
                int i_new = i - k;
                if( i_new < 0 || grid[i_new][j] == '#' )
                    break;
                int v = i_new * n + j;
                g[u].push_back(v);
                if( A[v] == 1001 ) {
                    A[v] = turns+1;
                    pq.push({i_new,j,turns+1});
                }
            }
        }

        return A[row_food * n + col_food];
    }

    int seen[64][64][1001]; // mouse,cat,player
    int ms[64];

    // objective: mouse reach food, cat catch mouse
    int dfs(vector<int> mg[], vector<int> cg[], int mouse, int cat, int food, int turns) {
        int player = turns % 2; // 0 mouse, 1 cat
        /*
        cout << "turns " << turns;
        cout << " mouse " << mouse << " cat " << cat << " player ";
        if( player == 0 ) cout << "MOUSE"; else cout << "CAT  ";
        cout << endl;
        */

        // turns even -> mouse turn, turns odd -> cat turn
        // return 1 mouse win, 0 cat win

        if( turns > 1000 )
           return 0;


        if( mouse == food ) {
            // cout << " mouse at food" << endl;
            // must be mouse turn
            // return seen[mouse][cat][0] = 1; // mouse win
            return 1;
        }


        // cout << " state " << seen[mouse][cat][turns] << endl;
        if( seen[mouse][cat][turns] != -1 )
           return seen[mouse][cat][turns];
        /*
        cout << " state " << seen[mouse][cat][player] << endl;
        if( seen[mouse][cat][player] != -1 )
           return seen[mouse][cat][player];
        */

        // seen[mouse][cat][player] = -1;

        if( player == 0 )
            ms[mouse] = 1;

        int ret = player == 0 ? 0 : 1;

        if( player == 0 ) {  // mouse turn

            // mouse would have the option to stay in place
            // but that does not make sense
            for(int i = 0; i < mg[mouse].size(); ++i) {
                int mouse_new = mg[mouse][i];
                if( mouse_new != cat && !ms[mouse_new] ) {
                    // cout << "mouse " << mouse << " cat " << cat << " mouse to " << mouse_new << endl;
                    if( dfs(mg,cg,mouse_new,cat,food,turns+1) ) {
                        ret = 1; // mouse win
                        break;
                    }
                }
            }

        } else {                 // cat turn

            for(int i = 0; i < cg[cat].size(); ++i) {
                int cat_new = cg[cat][i];
                // cout << "cat " << cat << " to " << cat_new << endl;
                if( cat_new == mouse ) {
                    ret = 0;   // cat win
                    break;
                }
                if( !dfs(mg,cg,mouse,cat_new,food,turns+1) ) {
                    ret = 0; // cat win
                    break;
                }
            }

            if( ret == 1 ) {
                // dont move
                if( !dfs(mg,cg,mouse,cat,food,turns+1) ) {
                    ret = 0;        // cat win
                }
            }
        }

        // backtrack
        if( player == 0 )
            ms[mouse] = 0;

        /*
        cout << "turns " << turns;
        cout << " mouse " << mouse << " cat " << cat << " player ";
        if( player == 0 ) cout << "MOUSE"; else cout << "CAT  ";
        if( ret == 1 ) cout << " MOUSE wins"; else cout << " CAT wins";
        cout << endl;
        */

        return seen[mouse][cat][turns] = ret;
        // return seen[mouse][cat][player] = ret;
        return ret;
    }

public:
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        // from game description:
        // game can end in 4 ways:
        //     If Cat occupies the same position as Mouse, Cat wins.
        //     If Cat reaches the food first, Cat wins.
        //     If Mouse reaches the food first, Mouse wins.
        //     If Mouse cannot get to the food within 1000 turns, Cat wins.

        // mouse goal: reach food and don't get caught
        // cat goal:   reach food or catch mouse

        // walls could prevent either mouse or cat getting to the food
        // hence: if mouse has no path to food, cat wins
        //            (regardless of cat being able to reach food or not)
        //        if mouse has a path to the food, but the cat doesn't, mouse wins

        // if the cat can reach food before the mouse can
        //     (consider mouse moves first), cat wins
        //     even though the cat cannot jump over the mouse, in which case
        //     cat would just eat mouse

        m = grid.size();
        n = grid[0].size();

        // locate the initial position of the mouse, cat and food
        int row_mouse,col_mouse,row_cat,col_cat;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 'M' ) {
                    row_mouse = i;
                    col_mouse = j;
                } else if( grid[i][j] == 'C' ) {
                    row_cat = i;
                    col_cat = j;
                } else if( grid[i][j] == 'F' ) {
                    row_food = i;
                    col_food = j;
                }

        // can mouse reach food?
        int ma[n*m];
        for(int i = 0; i < n*m; ++i)
            ma[i] = 1001;
        vector<int> mg[m*n];
        int tm = can_reach_food(grid,row_mouse,col_mouse,mouseJump,ma,mg);
        // cout << "mouse " << tm << endl;
        if( tm == 1001 )
            return false; // cat wins

        // can cat reach food? we already know that the mouse can
        // if the cat cannot reach the food, the cat can also not reach the mouse
        int ca[n*m];
        for(int i = 0; i < n*m; ++i)
            ca[i] = 1001;
        vector<int> cg[m*n];
        int tc = can_reach_food(grid,row_cat,col_cat,catJump,ca,cg);
        // cout << "cat " << tc << endl;
        if( tc == 1001 )
            return true; // mouse wins

        if( tc < tm )
            return false; // cat wins

        /*
        cout << "mouse graph" << endl;
        for(int i = 0; i < m*n; ++i) {
            cout << i << ": ";
            for(int j = 0; j < mg[i].size(); ++j)
                cout << mg[i][j] << " ";
            cout << endl;
        }
        cout << "mouse dist" << endl;
        for(int i = 0; i < m*n; ++i)
            cout << i << ":" << ma[i] << " ";
        cout << endl;
        cout << "cat dist" << endl;
        for(int i = 0; i < m*n; ++i)
            cout << i << ":" << ca[i] << " ";
        cout << endl;
        */

        // DFS
        // has the mouse a way from start to food where it cannot be caught by the cat?
        // meaning at each node it would need to be able to be there before the cat
        memset(seen,-1,sizeof seen);
        /*
        for(int i = 0; i < n*m; ++i) {
            for(int j = 0; j < n*m; ++j) {
                seen[i][j][0] = -2;
                seen[i][j][1] = -2;
            }
        }
        */
        memset(ms,0,sizeof ms);

        int mouse = row_mouse * n + col_mouse;
        int cat   = row_cat * n + col_cat;
        int food  = row_food * n + col_food;
        return dfs(mg,cg,mouse,cat,food,0);
    }
};
