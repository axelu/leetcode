
// 3578. Count Partitions With Max-Min Difference at Most K
// https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/





class Solution {
private:
    const long mod = 1000000007;

    pair<int,int> * t;

    pair<int, int> combine(pair<int,int> a, pair<int,int> b) {
        return make_pair(min(a.first,b.first),max(a.second,b.second));
    }

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(a[tl],a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    int get_first_greater(int v, int tl, int tr, int l, int r, int x) {
        if(tl > r || tr < l) return -1;
        if(t[v].second <= x) return -1;

        if (tl== tr) return tl;

        int tm = tl + (tr-tl)/2;
        int left = get_first_greater(2*v, tl, tm, l, r, x);
        if(left != -1) return left;
        return get_first_greater(2*v+1, tm+1, tr, l ,r, x);
    }

    int get_first_smaller(int v, int tl, int tr, int l, int r, int x) {
        if(tl > r || tr < l) return -1;
        if(t[v].first >= x) return -1;

        if (tl== tr) return tl;

        int tm = tl + (tr-tl)/2;
        int left = get_first_smaller(2*v, tl, tm, l, r, x);
        if(left != -1) return left;
        return get_first_smaller(2*v+1, tm+1, tr, l ,r, x);
    }



public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();

        // segment tree min and max, return first greater or smaller
        pair<int,int> T[4*50000];
        t = T;
        build(nums.data(),1,0,n-1);

        vector<long> v(n);
        v[n-1] = 1L;
        vector<long> s(n+1);
        s[n] = 0L;
        s[n-1] = 1L;


        int e = n-1;
        long addend;

        for(int i = n-2; i >= 0; --i) {
            int x = nums[i];

            int a = get_first_greater(1,0,n-1,i+1,e,x+k);
            // cout << "i " << i << " a " << a << endl;

            int b = get_first_smaller(1,0,n-1,i+1,e,x-k);
            // cout << "i " << i << " b " << b << endl;
            // cout << "i " << i << " a " << a << " b " << b << endl;

            int e_new;
            if( a == -1 && b == -1 ) {
                // e = n-1;
                e_new = e;
                addend = 1L;
                if( e < n-1 )
                    addend = v[e+1];

            } else if( a == - 1) {
                e = b; e_new = b-1;
                addend = 0L;
            } else if( b == -1 ) {
                e = a; e_new = a-1;
                addend = 0L;
            } else {
                e = min(a,b); e_new = e-1;
                addend = 0L;
            }

            // cout << "e " << e << endl;
            v[i] = (s[i+1] - s[e+1]) % mod; // watch out for it becoming negative
            if( v[i] < 0L )
                v[i] += mod;
            v[i] = (v[i] + addend) % mod;
            // cout << "v[" << i << "] " << v[i] << endl;
            s[i] = (v[i] + s[i+1]) % mod;

            e = e_new;
        }

        return (int)v[0];
    }
};
