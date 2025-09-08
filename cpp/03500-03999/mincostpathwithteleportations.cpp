
// 3651. Minimum Cost Path with Teleportations
// https://leetcode.com/problems/minimum-cost-path-with-teleportations/


class Solution {
private:
    // debug
    void print_grid(int k, vector<vector<int>>& grid) {
        cout << "k " << k << endl;
        int m = grid.size();
        int n = grid.size();
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j)
                cout << grid[i][j] << " ";
            cout << endl;
        }
        return;
    }

    int get_min(int * t, int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INT_MAX;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return min(get_min(t, v+1, tl, tm, l, min(r, tm)),
                   get_min(t, v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int * t, int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = min(t[v], new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(t, v+1, tl, tm, pos, new_val);
            else
                update(t, v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = min(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int dest_val = grid[m-1][n-1];
        // edge case
        if( k > 0 && grid[0][0] >= dest_val )
            return 0;

        // idea
        // eplore grid by increasing values for all 0 <= k' <= k
        // only keep the best for each value, k, teleported
        // with that we only explore 1 cell (the best) for value <= curr cell value
        // unless k is 0

        // Buttom Up DP

        // in all cases with a k > 0, we can teleport from a cell
        // to any cell with a eq or lt value for a cost of 0
        // we can work with an offset of dest_val for our range data structure
        // let dest_val = 5 
        //                    x
        // grid_val 0 1 2 3 4 5 6 7 8 9 10 ...
        //          <--------
        // grid_val 0 1 2 3 4


        int _grid[80][80];

        // solve for k = 0;        
        int _pre_t[20000]; int * pre_t = _pre_t;

        // init our segment tree with large value up to 2 * (dest_val;
        for(int i = 0; i < 2*dest_val; ++i)
            pre_t[i] = INT_MAX;

        for(int i = m-1; i >= 0; --i) {
            for(int j = n-1; j >= 0; --j) {
                int val = grid[i][j];

                // at destination
                if( i == m-1 && j == n-1 ) {
                    _grid[i][j] = val;
                    continue;
                }

                // right
                int right = INT_MAX;
                int i_new = i;
                int j_new = j+1;
                if( j_new < n )
                    right = _grid[i_new][j_new];       

                // down
                int down = INT_MAX;
                i_new = i+1;
                j_new = j;
                if( i_new < m )
                    down = _grid[i_new][j_new]; 
                
                if( i == 0 && j == 0) {
                    _grid[i][j] = min(right, down);
                } else {
                    _grid[i][j] = val + min(right, down);
                }

                if( val < dest_val )
                    update(pre_t, 1, 0, dest_val-1, val, min(right, down));
            }
        }

        if( k == 0 )
            return _grid[0][0];

        // solve for k > 0

        // setup current segment tree
        int _cur_t[20000]; int * cur_t = _cur_t;

        for(int _k = 1; _k <= k; ++_k) {
            
            // init our current segment tree with large value up to 2 * (dest_val;
            for(int i = 0; i < 2*dest_val; ++i)
                cur_t[i] = INT_MAX;

            for(int i = m-1; i >= 0; --i) {
                for(int j = n-1; j >= 0; --j) {
                    int val = grid[i][j];

                    // at destination
                    if( i == m-1 && j == n-1 ) {
                        _grid[i][j] = val;
                        continue;
                    }

                    // teleport to destination
                    if( val >= dest_val ) {
                        _grid[i][j] = val;
                        continue;
                    }

                    // we know that we have already solved for
                    // cell below and cell to right [for curr k]
                    // right
                    int right = INT_MAX;
                    int i_new = i;
                    int j_new = j+1;
                    if( j_new < n )
                        right = _grid[i_new][j_new];       

                    // down
                    int down = INT_MAX;
                    i_new = i+1;
                    j_new = j;
                    if( i_new < m )
                        down = _grid[i_new][j_new]; 

                    // if we teleport, we can reach any cell where
                    // grid[i'][j'] <= grid[i][j], and we would arrive
                    // at grid[i'][j'] with k-1, and we already have
                    // solved for k-1.
                    // so all we need to do is look at our prior results
                    // and get the best result (min) for all grid cells
                    // with a value <= grid[i][j]
                    // which would be a range min query
                    int teleport = get_min(pre_t, 1, 0, dest_val-1, 0, val);

                    if( i == 0 && j == 0) {
                        _grid[i][j] = min({right, down, teleport});
                    } else {
                        _grid[i][j] = val + min({right, down, teleport});
                    }

                    update(cur_t, 1, 0, dest_val-1, val, min({right, down, teleport}));
                }

            }

            // flip current tree to pretree
            swap(cur_t, pre_t);
        }

        return _grid[0][0];
    }
};


// passes 617/880 test cases as of 9/1/2025, then TLE
// test case 617 runs in about ~335ms, correct result, but it is obviously too slow
// Note: test case from below 515 runs in about ~22ms

class Solution {
private:
    int m, n;
    int dest_val;
    map<int, vector<pair<int,int>>> mp; // key: grid cell val, value: list of cells with that value

    // int mem_justk[80][80][11];
    int mem[80][80][11][2];

    int rec(vector<vector<int>>& grid, int i, int j, int k, bool teleported) {
        int val = grid[i][j];
        int cost = teleported || (i == 0 && j == 0) ? 0 : val;

        if( k > 0 && dest_val <= val )
            return cost;

        if( i == m-1 && j == n-1 )
            return cost;

        // TODO if we have been here with a better k (eq or gt k) and same
        // teleported, no point going further. In fact it does not matter
        // if teleported here or not, only diff is to include our val or not


        if( mem[i][j][k][teleported] != -1 )
            return mem[i][j][k][teleported];

        int mn = INT_MAX;

        // right
        int i_new = i;
        int j_new = j+1;
        if( j_new < n )
            mn = rec(grid, i_new, j_new, k, false);

        // down
        i_new = i+1;
        j_new = j;
        if( i_new < m )
            mn = min(mn, rec(grid, i_new, j_new, k, false));

        // teleport
        if( k > 0 ) {
            int k_new = k-1;
            auto it = mp.find(val); // it is guaranteed that val is in map
            for(;; --it) {
                for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                    i_new = iti->first;
                    j_new = iti->second;
                    if( i_new == i && j_new == j )
                        continue;
                    mn = min(mn, rec(grid, i_new, j_new, k_new, true));
                }
                if( it == mp.begin() )
                    break;
            }
        }

        return mem[i][j][k][teleported] = cost + mn;
    }

public:
    int minCost(vector<vector<int>>& grid, int k) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        // keep pruning
        //      if cost >= best answer
        //      if key[cost,rem k] at a given cell already seen
        //      [i][j][cost][remk] -> 80*80*(1,600,000)*10 = 102400000000
        //
        //  cost    remaining k
        //  gt eq   eq              prune
        //  gt eq   lt              prune
        //  gt eq   gt              keep, prefer
        //  lt      eq              keep, prefer
        //  lt      lt              keep
        //  lt      gt              keep, prefer best
        //  distilled: if cost is less or remaining k is greater, then keep
        //  also consider exploring from grid value smallest to largest
        //  at a given cell we have three options:
        //      go right OR
        //      go down OR
        //      go to a cell with <= value, we would only go to the best cell,
        //      but problem is that we can also go to eq value cells, so which
        //      of those do we explore first, we wouldn't know the result of the
        //      others, so chicken-egg problem (would be different if strictly smaller)

        dest_val = grid[m-1][n-1];

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                mp[grid[i][j]].push_back({i,j});

        memset(mem,-1,sizeof mem);
        return rec(grid, 0, 0, k, false);
    }
};

// passes 514/880 test cases as of 9/1/2025, then TLE
// test case 515 runs in about ~2300ms, correct result, but it is obviously too slow

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // keep pruning
        //      if cost >= best answer
        //      if key[cost,rem k] at a given cell already seen
        //      [i][j][cost][remk] -> 80*80*(1,600,000)*10 = 102400000000
        //
        //  cost    remaining k
        //  gt eq   eq              prune
        //  gt eq   lt              prune
        //  gt eq   gt              keep, prefer
        //  lt      eq              keep, prefer
        //  lt      lt              keep
        //  lt      gt              keep, prefer best
        //  distilled: if cost is less or remaining k is greater, then keep
        //  also consider exploring from grid value smallest to largest
        //  at a given cell we have three options:
        //      go right OR
        //      go down OR
        //      go to a cell with <= value, we would only go to the best cell,
        //      but problem is that we can also go to eq value cells, so which
        //      of those do we explore first, we wouldn't know the result of the
        //      others, so chicken-egg problem (would be different if strictly smaller)

        int dest_val = grid[m-1][n-1];

        map<int, vector<pair<int,int>>> mp; // key: grid cell val, value: list of cells with that value
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                mp[grid[i][j]].push_back({i,j});

        // init very high cost (INT_MAX) and very low k (zero)
        int A[80][80][2];
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                A[i][j][0] = INT_MAX;   // cost
                A[i][j][1] = 0;         // remaining k
            }

        // array<int,4> 0: cost 1: remaining k 2: i 3: j
        auto cmp = [](const array<int,4>& a, const array<int,4>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,4>,vector<array<int,4>>,decltype(cmp)> pq(cmp);

        pq.push({0, k, 0, 0});
        while( !pq.empty() ) {
            int cost = pq.top()[0];
            int remk = pq.top()[1];
            int i = pq.top()[2];
            int j = pq.top()[3];
            int val = grid[i][j];
            pq.pop();

            if( dest_val <= val )
                return cost;

            if( i == m-1 && j == n-1 )
                return cost;

            // right
            int i_new = i;
            int j_new = j+1;
            if( j_new < n ) {
                int cost_new = cost + grid[i_new][j_new];
                int remk_new = remk;
                if( cost_new < A[i_new][j_new][0] || remk_new > A[i_new][j_new][1] ) {

                    // TODO move a to private, make this a function as we repeat this three times
                    if( (cost_new < A[i_new][j_new][0] && remk_new >= A[i_new][j_new][1]) ||
                        (cost_new <= A[i_new][j_new][0] && remk_new > A[i_new][j_new][1]) ) {
                        A[i_new][j_new][0] = cost_new;
                        A[i_new][j_new][1] = remk_new;
                    }

                    pq.push({cost_new, remk_new, i_new, j_new});
                }
            }

            // down
            i_new = i+1;
            j_new = j;
            if( i_new < m ) {
                int cost_new = cost + grid[i_new][j_new];
                int remk_new = remk;
                if( cost_new < A[i_new][j_new][0] || remk_new > A[i_new][j_new][1] ) {

                    if( (cost_new < A[i_new][j_new][0] && remk_new >= A[i_new][j_new][1]) ||
                        (cost_new <= A[i_new][j_new][0] && remk_new > A[i_new][j_new][1]) ) {
                        A[i_new][j_new][0] = cost_new;
                        A[i_new][j_new][1] = remk_new;
                    }

                    pq.push({cost_new, remk_new, i_new, j_new});
                }
            }

            // Teleportation
            if( remk > 0 ) {
                int cost_new = cost;
                int remk_new = remk-1;
                auto it = mp.find(val); // it is guaranteed that val is in map
                for(;; --it) {
                    for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                        i_new = iti->first;
                        j_new = iti->second;
                        if( cost_new < A[i_new][j_new][0] || remk_new > A[i_new][j_new][1] ) {

                            if( (cost_new < A[i_new][j_new][0] && remk_new >= A[i_new][j_new][1]) ||
                                (cost_new <= A[i_new][j_new][0] && remk_new > A[i_new][j_new][1]) ) {
                                A[i_new][j_new][0] = cost_new;
                                A[i_new][j_new][1] = remk_new;
                            }

                            pq.push({cost_new, remk_new, i_new, j_new});
                        }
                    }
                    if( it == mp.begin() )
                        break;
                }
            }
        }

        return -1; // we should never get here

        // TODO explore the option of starting from destination
    }
};
