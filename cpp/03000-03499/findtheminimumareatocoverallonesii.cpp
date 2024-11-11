

// 3197. Find the Minimum Area to Cover All Ones II
// https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/ 






class Solution {
private:
    struct T {
        int xmin;
        int ymin;
        int xmax;
        int ymax;
        T() : xmin(1000), ymin(1000), xmax(-1000), ymax(-1000) {}
    };

    int n,m;
    vector<vector<T*>> t; // 2D segment tree

    T * combine(T* a, T* b) {
        T * nd = new T();
        nd->xmin = min(a->xmin,b->xmin);
        nd->ymin = min(a->ymin,b->ymin);
        nd->xmax = max(a->xmax,b->xmax);
        nd->ymax = max(a->ymax,b->ymax);
        return nd;
    }

    void build_y(int vx, int lx, int rx, int vy, int ly, int ry, vector<vector<int>>& a) {
        if (ly == ry) {
            if (lx == rx) {
                T * nd = new T();
                if( a[lx][ly] ) {
                    nd->xmin = lx;
                    nd->ymin = ly;
                    nd->xmax = lx;
                    nd->ymax = ly;
                }
                t[vx][vy] = nd;

            } else {
                t[vx][vy] = combine(t[vx*2][vy], t[vx*2+1][vy]);

            }
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2, ly, my, a);
            build_y(vx, lx, rx, vy*2+1, my+1, ry, a);
            t[vx][vy] = combine(t[vx][vy*2], t[vx][vy*2+1]);
        }
    }

    void build_x(int vx, int lx, int rx, vector<vector<int>>& a) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx*2, lx, mx, a);
            build_x(vx*2+1, mx+1, rx, a);
        }
        build_y(vx, lx, rx, 1, 0, m-1, a);
    }

    T * get_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry)
            return new T();
        if (ly == tly && try_ == ry)
            return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return combine(get_y(vx, vy*2, tly, tmy, ly, min(ry, tmy)),
                       get_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry));
    }

    T * get_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return new T();
        if (lx == tlx && trx == rx)
            return get_y(vx, 1, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return combine(get_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry),
                       get_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry));
    }

    int mem[30][30][30][30];

    int area(int r1, int r2, int c1, int c2) {
        if( mem[r1][r2][c1][c2] != -1 )
            return mem[r1][r2][c1][c2];

        T * nd = get_x(1,0,n-1,r1,r2,c1,c2);
        int a = nd->xmax - nd->xmin + 1;
        int b = nd->ymax - nd->ymin + 1;

        return mem[r1][r2][c1][c2] = a * b;
    }

public:
    int minimumSum(vector<vector<int>>& grid) {
        n = grid.size();    // rows
        m = grid[0].size(); // cols

        // TODO special case if n == 1 || m == 1

        t = vector(4*n,vector<T*>(4*m));
        build_x(1,0,n-1,grid);

        int ans = INT_MAX;

        memset(mem,-1,sizeof mem);

        // pass1
        for(int j = 0; j < m-1; ++j) {
            // area left [0,n-1][0,j]
            int lft = area(0,n-1,0,j);

            // area right
            // vertical split
            for(int k = j+1; k < m-1; ++k) {
                int rgt_lft = area(0,n-1,j+1,k);
                int rgt_rgt = area(0,n-1,k+1,m-1);
                ans = min(ans, lft + rgt_lft + rgt_rgt);
            }
            // horizontal split
            for(int k = 0; k < n-1; ++k) {
                int rgt_top = area(0,k,j+1,m-1);
                int rgt_btm = area(k+1,n-1,j+1,m-1);
                ans = min(ans, lft + rgt_top + rgt_btm);
            }
        }
        // cout << "after pass1 " << ans << endl;

        // pass2
        for(int i = 0; i < n-1; ++i) {
            // area top [0,i][0,m-1]
            int top = area(0,i,0,m-1);

            // area bottom
            // vertical split
            for(int k = 0; k < m-1; ++k) {
                int btm_lft = area(i+1,n-1,0,k);
                int btm_rgt = area(i+1,n-1,k+1,m-1);
                ans = min(ans, top + btm_lft + btm_rgt);
            }
            // horizontal split
            for(int k = i+1; k < n-1; ++k) {
                int btm_top = area(i+1,k,0,m-1);
                int btm_btm = area(k+1,n-1,0,m-1);
                ans = min(ans, top + btm_top + btm_btm);
            }
        }
        // cout << "after pass2 " << ans << endl;

        // pass3
        for(int j = 0; j < m-1; ++j) {
            // area right
            int rgt = area(0,n-1,j+1,m-1);

            // area left
            // vertical split
            for(int k = 0; k < j; ++k) {
                int lft_lft = area(0,n-1,0,k);
                int lft_rgt = area(0,n-1,k+1,j);
                ans = min(ans, rgt + lft_lft + lft_rgt);
            }
            // horizontal split
            for(int k = 0; k < n-1; ++k) {
                int lft_top = area(0,k,0,j);
                int lft_btm = area(k+1,n-1,0,j);
                ans = min(ans, rgt + lft_top + lft_btm);
            }
        }
        // cout << "after pass3 " << ans << endl;

        // pass4
        for(int i = 0; i < n-1; ++i) {
            // area bottom
            int btm = area(i+1,n-1,0,m-1);

            // area top
            // vertical split
            for(int k = 0; k < m-1; ++k) {
                int top_lft = area(0,i,0,k);
                int top_rgt = area(0,i,k+1,m-1);
                ans = min(ans, btm + top_lft + top_rgt);
            }
            // horizontal split
            for(int k = 0; k < i; ++k) {
                int top_top = area(0,k,0,m-1);
                int top_btm = area(k+1,i,0,m-1);
                ans = min(ans, btm + top_top + top_btm);
            }
        }
        // cout << "after pass4 " << ans << endl;

        return ans;
    }
};
