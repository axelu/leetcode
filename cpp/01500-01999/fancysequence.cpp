
// 1622. Fancy Sequence
// https://leetcode.com/problems/fancy-sequence/



class Fancy {
private:
    array<long,2> * t;
    int i;
    long arr[100000];
    long mod = 1000000007;

    void update(int v, int tl, int tr, int l, int r, int op, long x) {
        // op = operation, 0 add, 1 multiply

        if (l > r)
            return; // bad index

        if (l == tl && r == tr) {
            if( op == 0 ) {
                t[v][0] = (t[v][0] + x) % mod;
            } else {
                t[v][0] = (t[v][0] * x) % mod;
                t[v][1] = (t[v][1] * x) % mod;
            }
            return;
        }

        int mid = (tl + tr) / 2;

        if( r <= mid)     // query falls in left subtree
            return update(v*2,tl,mid,l,r,op,x);
        else if( l > mid) // query falls in right subtree
            return update(v*2+1,mid+1,tr,l,r,op,x);

        // query covers the mid point
        // traverse [l,mid]
        update(v*2,tl,mid,l,mid,op,x);
        // traverse [mid+1,r]
        update(v*2+1,mid+1,tr,mid+1,r,op,x);

        return;
    }

    long get(int v, int tl, int tr, int l, int r, long sum, long m, long x) {
        // cout << "v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        // l == r

        long sum_new = (((m * t[v][0]) % mod) + sum) % mod;
        long m_new   = (m * t[v][1]) % mod;

        // we either reached the end OR
        // we go left or right, because l == r

        if (l == tl && r == tr)
            return (((x * m_new) % mod) + sum_new) % mod;

        int mid = (tl + tr) / 2;
        if( r <= mid)     // query falls in left subtree
            return get(v*2,tl,mid,l,r,sum_new,m_new,x);
        else
            return get(v*2+1,mid+1,tr,l,r,sum_new,m_new,x);
    }

public:
    Fancy() {
        // we are building a segment tree that will hold at each node
        // the cumulative sum adjusted by the current multiplier and
        // the cumulative multiplier
        // initially at each node the cumulative sum is 0 and
        // the cumulative multiplier is 1
        array<long,2> T[400000];
        t = T;
        for(int i = 0; i < 400000; ++i)
            t[i] = {0L,1L};

        i = -1;
    }

    void append(int val) {
        ++i;
        arr[i] = val;
    }

    void addAll(int inc) {
        if( i == -1 )
            return;

        update(1,0,99999,0,i,0,inc);
    }

    void multAll(int m) {
        if( i == -1 )
            return;

        update(1,0,99999,0,i,1,m);
    }

    int getIndex(int idx) {
        if( idx > i )
            return -1;

        return get(1,0,99999,idx,idx,0,1,arr[idx]);
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
