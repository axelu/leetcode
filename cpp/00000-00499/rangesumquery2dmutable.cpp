
// 308. Range Sum Query 2D - Mutable
// https://leetcode.com/problems/range-sum-query-2d-mutable/



// https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-11
class NumMatrix {
private:
    int n,m;
    vector<vector<int>> t;

    void build_y(int vx, int lx, int rx, int vy, int ly, int ry, vector<vector<int>>& a) {
        if (ly == ry) {
            if (lx == rx)
                t[vx][vy] = a[lx][ly];
            else
                t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2, ly, my, a);
            build_y(vx, lx, rx, vy*2+1, my+1, ry, a);
            t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
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

    int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry)
            return 0;
        if (ly == tly && try_ == ry)
            return t[vx][vy];
        int tmy = (tly + try_) / 2;
        return sum_y(vx, vy*2, tly, tmy, ly, min(ry, tmy))
               + sum_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
    }

    int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx)
            return 0;
        if (lx == tlx && trx == rx)
            return sum_y(vx, 1, 0, m-1, ly, ry);
        int tmx = (tlx + trx) / 2;
        return sum_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry)
               + sum_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
    }

    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
        if (ly == ry) {
            if (lx == rx)
                t[vx][vy] = new_val;
            else
                t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            if (y <= my)
                update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
            else
                update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
            t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
        }
    }

    void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx)
                update_x(vx*2, lx, mx, x, y, new_val);
            else
                update_x(vx*2+1, mx+1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
    }
public:
    NumMatrix(vector<vector<int>>& matrix) {
        n = matrix.size();
        if( n == 0 ) return;
        m = matrix[0].size();
        if( m == 0 ) return;
        t = vector(4*n,vector<int>(4*m));
        build_x(1,0,n-1,matrix);
    }

    void update(int row, int col, int val) {
        update_x(1,0,n-1,row,col,val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if( n == 0 || m == 0 ) return 0;
        return sum_x(1,0,n-1,row1,row2,col1,col2);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
