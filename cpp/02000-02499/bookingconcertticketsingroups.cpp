
// 2286. Booking Concert Tickets in Groups
// https://leetcode.com/problems/booking-concert-tickets-in-groups/




class BookMyShow {
private:
    // segment tree max free contigous seats, sum free seats
    pair<int,long> t[200000];
    int N,M;

    pair<int,long> combine(pair<int,long>& a, pair<int,long>& b) {
        pair<int,long> ret;
        ret.first = max(a.first,b.first);
        ret.second = a.second + b.second;
        return ret;
    }

    void build(int m, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(m,m);
        } else {
            int tm = (tl + tr) / 2;
            build(m, v*2, tl, tm);
            build(m, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    // range max query
    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v].first;
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v*2, tl, tm, l, min(r, tm)),
                   get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    vector<int> update_gather(int v, int tl, int tr, int k) {
        if( k > t[v].first )
            return {};

        if (tl == tr) {
            int s = M-t[v].first;
            int free = t[v].first-k;
            t[v].first = t[v].second = free;
            return {tl,s};
        } else {
            int tm = (tl + tr) / 2;
            auto ret = update_gather(v*2, tl, tm, k);
            if( ret.empty() )
                ret = update_gather(v*2+1, tm+1, tr, k);
            t[v] = combine(t[v*2], t[v*2+1]);
            return ret;
        }
    }

    // sum range query
    long get_sum(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v].second;
        }
        int tm = (tl + tr) / 2;
        return get_sum(v*2, tl, tm, l, min(r, tm)) +
               get_sum(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    int update_scatter(int v, int tl, int tr, int k) {
        // cout << "update_scatter v " << v << " tl " << tl << " tr " << tr << " k " << k << endl;
        // TODO could we do lazy propagation of this?
        if( k == 0 )
            return 0;

        if (tl == tr) {
            int d = t[v].first - k;
            if( d < 0 ) {
                t[v].first = t[v].second = 0;
                return k + d;
            } else {
                t[v].first = t[v].second = d;
                return k;
            }
        } else {
            int tm = (tl + tr) / 2;
            int seated_left = update_scatter(v*2, tl, tm, k);
            int seated_right = update_scatter(v*2+1, tm+1, tr, k-seated_left);
            t[v] = combine(t[v*2], t[v*2+1]);
            return seated_left+seated_right;
        }
    }

public:
    BookMyShow(int n, int m) {
        // 1 <= n <= 50000 rows
        // 1 <= m <= 1000000000 seats aka cols
        // worst case our concert hall has 50000 x 1000000000 = 50000000000000 seats
        N = n;
        M = m;
        build(m,1,0,N-1);
    }

    vector<int> gather(int k, int maxRow) {
        int mx = get_max(1,0,N-1,0,maxRow);
        if( mx < k )
            return {};
        // we know now that there is a row in range [0,maxRow] inclusive
        // that can seat k people [together]
        // lets update the lowest row possible
        return update_gather(1,0,N-1,k);
    }

    bool scatter(int k, int maxRow) {
        long sum = get_sum(1,0,N-1,0,maxRow);
        // cout << "scatter sum begin " << sum << endl;
        if( sum < k )
            return false;
        // we know now that there are k seats in rows [0,maxRow] inclusive
        // lets fill those starting with lowest row possible
        // till all k people are seated
        update_scatter(1,0,N-1,k);
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */
