
// 3802. Number of Ways to Paint Sheets
// https://leetcode.com/problems/number-of-ways-to-paint-sheets/



class Solution {
private:
    const long long mod = 1000000007LL;

    /*
    long long t[400000]; // segment tree (sum), lazy propagation, range addition, range query, point query
    long long lazy[400000];

    void build(vector<long long>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    void push(int v) {
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0LL;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, long long addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = query(v*2, tl, tm, tl, tm) + query(v*2+1, tm+1, tr, tm+1, tr);
        }
    }

    // range query get sum
    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0LL;
        if (l == tl && tr == r)
            return t[v] + ((1 + tr - tl) * lazy[v]);
        int tm = (tl + tr) / 2;
        return (1 + r - l) * lazy[v] +
               query(v*2, tl, tm, l, min(r, tm)) +
               query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    // point query
    long long get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            // return t[v];
            return lazy[v] + t[v];

        // push(v); // alternatively we could add lazy[v] along the way
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            // return get(v*2, tl, tm, pos);
            return lazy[v] + get(v*2, tl, tm, pos);
        else
            // return get(v*2+1, tm+1, tr, pos);
            return lazy[v] + get(v*2+1, tm+1, tr, pos);
    }
    */
public:
    int numberOfWays(int n, vector<int>& limit) {
        long long ans = 0LL;

        // it makes no sense to have a limit[i] >= n
        for(auto& _limit: limit)
            if( _limit >= n )
                _limit = n-1;

        // 2 <= limit.size() <= 1e5; in other words at most 1e5 colors

        //                         A B C D E  color idx
        // example n = 5; limit = [2,3,3,4,4]
        // let us assume we are using color A in the left contiguous segment
        // we can color up to 3 left sheets with color B
        // sheet 01234
        //       B     we can use colors with limit >= 4: D, E       -> 2
        //       BB    we can use colors with limit >= 3: D, E, C    -> 3
        //       BBB   we can use colors with limit >= 2: D, E, C, A -> 4
        //                                                             ---
        //                                                              9
        // let us count colors by limit 2 3 4
        //                              1 2 2
        // prefixSum right to left      5 4 2 prefixSum total = 16 (prefixSum of prefixSum)
        // if we are using our color B (limit 3), we need to subtract it
        // basically a range addition in our prefix Sum (-1 in range 2..3)
        // let us count colors by limit 2 3 4
        //                              1 1 2
        // prefixSum right to left      4 3 2
        // so to answer our question for color B, we know
        // we can use colors with limit >= 2
        // let us count colors by limit 2 3 4
        // prefixSum right to left      4 3 2
        //                              ----- sum of count colors with limit >= 2 = 9 (4+3+2), which is what we need
        //
        // we will built a segment tree of the prefixSum (right to left)
        // for each color:
        //      do range addition (-1 to subtract the color we use) [1,limit of color]
        //      sum query [n-limit of color, max_limit]
        //      do range addition (+1 add the color back in) [1,limit of color]
        // because 1 <= limit[i] <= 1e9, we need coordinate compression
        // because 2 <- limit.size() <= 1e5, we can worse case have 1e5 different limits

        map<int,int> limitdic;
        for(int x: limit)
            limitdic.insert({x, -1});
        int m = 0;
        for(auto& p: limitdic)
            p.second = m++;

        // cout << "m " << m << endl;

        vector<long long> limitcnt(m, 0LL);
        for(int _limit: limit)
            ++limitcnt[limitdic[_limit]];

        vector<long long> prefixSum(m); // right to left, 0-indexed
        prefixSum[m-1] = limitcnt[m-1];
        for(int i = m-2; i >= 0; --i)
            prefixSum[i] = prefixSum[i+1] + limitcnt[i];


        // instead of increment by 1, we need to jump
        set<int> steps; // left lengths at which we need to calculate
        // left
        steps.insert(1);
        for(auto& p: limitdic)
            steps.insert(p.first + 1);
        // right
        for(auto& p: limitdic)
            steps.insert(n - p.first);

        auto lpptr = limitdic.begin();
        auto rpptr = limitdic.end();
        // int max_limit = min(n-1, limitdic.rbegin()->first);
        // int min_ll = n - max_limit;
        // for(int ll = min_ll; ll <= max_limit; ++ll) { // ll left_limit aka left_length
        for(auto it = steps.begin(); it != steps.end(); ++it) {
            int ll = *it;
            // cout << "ll " << ll << endl;

            // how many colors do we have with limit >= ll ?
            while( lpptr != limitdic.end() && lpptr->first < ll )
                ++lpptr;
            if( lpptr == limitdic.end() )
                break;

            long long lft_co_cnt = prefixSum[lpptr->second];

            int rl = n - ll; // rl right_limit aka right_length
            // how many colors do we have with limit >= rl ?
            while( rpptr != limitdic.begin() && prev(rpptr)->first >= rl )
                --rpptr;

            long long rgt_co_cnt = rpptr != limitdic.end() ? prefixSum[rpptr->second] : 0;
            if( rgt_co_cnt == 0 )
                continue;

            // don't double count
            // if ll <= rl  then all colors on right are also on left
            // if ll >  rl  then all colors on left are also on right
            long long res = 0;
            if( ll <= rl ) {
                res = ((lft_co_cnt * rgt_co_cnt) % mod) - rgt_co_cnt;
                if( res < 0 )
                    res += mod;
            } else {
                res = ((lft_co_cnt * rgt_co_cnt) % mod) - lft_co_cnt;
                if( res < 0 )
                    res += mod;
            }

            // cout << "ll " << ll << " res " << res << endl;

            // jump to next ll where either lft_co_cnt will change or rgt_co_cnt will change
            // let that index be ll_new, then we can multiply res by f = ll_new - ll
            long long f = *next(it) - ll;
            res = (res * f) % mod;
            ans = (ans + res) % mod;
        }


        return ans;

        /*
        // build segment tree from prefixSum
        build(prefixSum, 1, 0, m-1);
        memset(lazy,0,sizeof lazy);


        // for each color
        // TODO optimize: for each distinct limit, then multiply
        //                by numbers of colors we have with that limit
        for(int i = 0; i < limit.size(); ++i) {
            int _limit   = limit[i];
            int limitidx = limitdic[_limit];

            update(1, 0, m-1, 0, limitidx, -1LL);

            // we need to sum prefixSum for limits >= n - _limit
            int othercolorminlimit = max(n - _limit, 1);
            cout << "othercolorminlimit " << othercolorminlimit << endl;
            auto lb = limitdic.lower_bound(othercolorminlimit);
            int othercolorminlimit_idx = lb->second;
            // cout << "othercolorminlimit_idx " << othercolorminlimit_idx << endl;
            long long res = query(1, 0, m-1, othercolorminlimit_idx, m-1);
            cout << "color i " << i << " limit[i] " << limit[i] << " res " << res << endl;

            // we can have a case where we can make additional distinct paints
            long long f = othercolorminlimit - limitdic.begin()->first;
            cout << "f " << f << endl;
            if( f > 0LL ) {
                // we have f *  more distinct ways to paint sheets
                long long addend = get(1, 0, m-1, othercolorminlimit_idx);
                // cout << "addend " << addend << endl;
                res = (res + ((f * addend) % mod)) % mod;
            }
            cout << "color i " << i << " limit[i] " << limit[i] << " res " << res << endl;

            ans = (ans + res) % mod;

            update(1, 0, m-1, 0, limitidx,  1LL);
        }

        return ans;
        */
    }
};
