
// 3525. Find X Value of Array II
// https://leetcode.com/problems/find-x-value-of-array-ii/





class Solution {
private:
    struct T {
        int product;
        int remcnt[5]; // frequency count of prefix product remainders
        T(int x) {
            product = x;
            remcnt[0] = 0;
            remcnt[1] = 0;
            remcnt[2] = 0;
            remcnt[3] = 0;
            remcnt[4] = 0;;
        }
    };

    T * t[400000]; // segment tree, point update, range query

    int k;

    T * combine(T * a, T * b) {
        if( a->product == -1 )
            return b;
        if( b->product == -1 )
            return a;

        // int product = a->product * b->product;
        int product = ((a->product % k) * (b->product % k)) % k;
        T * ab = new T(product);
        int rem_left = a->product % k;
        for(int i = 0; i < 5; ++i) {
            // all from left
            ab->remcnt[i] += a->remcnt[i];
            // left remainder * all right remainders
            ab->remcnt[(rem_left * i) % k] += b->remcnt[i];
        }

        return ab;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = new T(a[tl]);
            t[v]->remcnt[a[tl] % k] = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v]->remcnt[t[v]->product % k] = 0;
            t[v]->product = new_val;
            t[v]->remcnt[new_val % k] = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, new_val);
            else
                update(v*2+1, tm+1, tr, pos, new_val);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    T * get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return new T(-1);
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get(v*2, tl, tm, l, min(r, tm)),
                       get(v*2+1, tm+1, tr, max(l, tm+1), r));
    }


public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
         // constraints
        // 1 <= nums[i] <= 1e9
        // 1 <= nums.length <= 1e5
        // 1 <= k <= 5

        // queries[i] == [indexi, valuei, starti, xi]

        this->k = k;
        int n = nums.size();

        build(nums, 1, 0, n-1);
        /*
        cout << "t[1]->product " << t[1]->product << endl;
        for(int i = 0; i < 5; ++i)
            cout << i << ":" << t[1]->remcnt[i] << " ";
        cout << endl;
        */

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int index = queries[i][0];
            int value = queries[i][1];
            int start = queries[i][2];
            int x = queries[i][3];

            update(1, 0, n-1, index, value);

            /*
            int left = 0;
            if( start > 0 ) {
                auto left_t = get(1, 0, n-1, 0, start-1);
                left = left_t->remcnt[x];
            }

            ans[i] = t[1]->remcnt[x] - left;
            */

            auto tq = get(1, 0, n-1, start, n-1);
            ans[i] = tq->remcnt[x];
        }

        return ans;
    }
};
