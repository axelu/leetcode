
// 1931. Painting a Grid With Three Different Colors
// https://leetcode.com/problems/painting-a-grid-with-three-different-colors/
// https://leetcode.com/contest/weekly-contest-249/problems/painting-a-grid-with-three-different-colors/




class Solution {
private:
    long MOD = 1000000007;

    void printBinary(int x) {
        for(int i = 31; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    // 1 row
    long rec1dim(int n, int pos, int parentColor, long mem[]) {
        if( pos == n )
            return 2;

        int memIdx = pos*3+parentColor;
        if( mem[memIdx] != -1 )
            return mem[memIdx];

        long ret;

        // the current cell can be painted in two colors
        if( parentColor == 0) {
            ret = rec1dim(n,pos+1,1,mem);
            ret = (ret + rec1dim(n,pos+1,2,mem)) % MOD;
        } else if( parentColor == 1 ) {
            ret = rec1dim(n,pos+1,0,mem);
            ret = (ret + rec1dim(n,pos+1,2,mem)) % MOD;
        } else {
            // parentColor == 2
            ret = rec1dim(n,pos+1,0,mem);
            ret = (ret + rec1dim(n,pos+1,1,mem)) % MOD;
        }

        return mem[memIdx] = ret;
    }

    void genCol0(int m, int pos, int path, vector<int>& ans) {
        if( pos == m ) {
            ans.push_back(path);
            return;
        }

        // parent color
        int bita = pos*2-2;
        int bitb = pos*2-1;
        int parentColor = 0 | ( path & (1<<bita));
        parentColor |= path & (1<<bitb);
        parentColor >>= bita;

        // current color bits
        int bitc = pos*2;
        int bitd = pos*2+1;


        if( parentColor == 0) {
            // current color 1
            path |= (1<<bitc);
            genCol0(m,pos+1,path,ans);
            // backtrack
            path ^= 1 << bitc;
            // current color 2
            path |= (1<<bitd);
            genCol0(m,pos+1,path,ans);
        } else if( parentColor == 1 ) {
            // current color 0
            genCol0(m,pos+1,path,ans);
            // current color 2
            path |= (1<<bitd);
            genCol0(m,pos+1,path,ans);
        } else {
            // parentColor == 2
            // current color 0
            genCol0(m,pos+1,path,ans);
            // current color 1
            path |= (1<<bitc);
            genCol0(m,pos+1,path,ans);
        }
    }

    unordered_map<int,vector<int>> cols;

    void genCol(int m, int pos, int parent, int top, vector<int>& ans) {
        if( pos == m ) {
            ans.push_back(top);
            return;
        }

        // parent is col the left

        // if pos is 0, only look to the left (and in memory)
        if( pos == 0 ) {

            auto f = cols.find(parent);
            if( f != cols.end() ) {
                ans = f->second;
                return;
            }

            // color to the left
            int leftColor = 0 | ( parent & 1 );
            leftColor |= parent & (1<<1);
            if( leftColor == 0 ) {
                genCol(m,pos+1,parent,1,ans);
                genCol(m,pos+1,parent,2,ans);
            } else if( leftColor == 1 ) {
                genCol(m,pos+1,parent,0,ans);
                genCol(m,pos+1,parent,2,ans);
            } else {
                // leftColor == 2
                genCol(m,pos+1,parent,0,ans);
                genCol(m,pos+1,parent,1,ans);
            }

            cols.insert({parent,ans});

        } else {
            // get left color
            int bita = pos*2;
            int bitb = pos*2+1;
            int leftColor = 0 | ( parent & (1<<bita));
            leftColor |= parent & (1<<bitb);
            leftColor >>= bita;

            // get top color
            int bitc = pos*2-2;
            int bitd = pos*2-1;
            int topColor = 0 | ( top & (1<<bitc));
            topColor |= top & (1<<bitd);
            topColor >>= bitc;

            if( leftColor == topColor ) {
                // we have two choices
                if( leftColor == 0 ) {
                     // current color 1
                    top |= (1<<bita);
                    genCol(m,pos+1,parent,top,ans);
                    // backtrack
                    top ^= 1 << bita;
                    // current color 2
                    top |= (1<<bitb);
                    genCol(m,pos+1,parent,top,ans);
                } else if( leftColor == 1 ) {
                    // current color 0
                    genCol(m,pos+1,parent,top,ans);
                    // current color 2
                    top |= (1<<bitb);
                    genCol(m,pos+1,parent,top,ans);
                } else {
                    // leftColor == 2
                    // current color 0
                    genCol(m,pos+1,parent,top,ans);
                    // current color 1
                    top |= (1<<bita);
                    genCol(m,pos+1,parent,top,ans);

                }
            } else {
                // we only have one choice
                if( (leftColor == 0 && topColor == 1) || (leftColor == 1 && topColor == 0) ) {
                    top |= (1<<bitb);
                    genCol(m,pos+1,parent,top,ans);
                } else if( (leftColor == 0 && topColor == 2) || (leftColor == 2 && topColor == 0) ) {
                    top |= (1<<bita);
                    genCol(m,pos+1,parent,top,ans);
                } else {
                    // (leftColor == 1 && topColor == 2) || (leftColor == 2 && topColor == 1)
                    genCol(m,pos+1,parent,top,ans);
                }
            }
        }
    }

    unordered_map<int,long> mem;

    long rec(int m, int n, int pos, int parent) {
        int key = pos << 10;
        key += parent;

        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // generate the next column(s)
        vector<int> nxt;
        genCol(m,0,parent,-1,nxt);

        if( pos == n-1 )
            return nxt.size();

        long ret = 0;

        for(int i = 0; i < nxt.size(); ++i) {
            ret = (ret + rec(m,n,pos+1,nxt[i])) % MOD;
        }

        mem.insert({key,ret});
        return ret;
    }
public:
    int colorTheGrid(int m, int n) {
        // 1 <= m <= 5,
        // 1 <= n <= 1000

        // colors red = 0, green = 1, blue = 2
        if( m == 1 && n == 1 )
            return 3;

        // 1 row
        if( m == 1 || n == 1 ) {
            int t = m == 1 ? n : m;

            long mem[t*3];memset(mem,-1,sizeof mem);

            long ret = rec1dim(t-1,1,0,mem); // take (ret*3)%MOD is also the answer
            ret = (ret + rec1dim(t-1,1,1,mem)) % MOD;
            ret = (ret + rec1dim(t-1,1,2,mem)) % MOD;

            return ret;
        }

        // idea
        // treat 2-5 rows still as 1 dimension aka 1 row
        // generate all possible target states for col 0 -> worst case m = 5 -> 48 states
        // then start with all those states in col 1 as usual

        vector<int> col0;
        genCol0(m,1,0,col0);
        /*
        for(int i = 0; i < col0.size(); ++i) {
            cout << "i " << i << " ";
            printBinary(col0[i]);
            cout << endl;
        }
        */

        long ret = 0;

        for(int i = 0; i < col0.size(); ++i) {
            ret = (ret + rec(m,n,1,col0[i])) % MOD;
        }

        return (ret*3L)%MOD;
    }
};
