
// https://leetcode.com/problems/count-integers-in-intervals/
// 2276. Count Integers in Intervals




class CountIntervals {
private:
    // as our 'leaves' aka smallest segments are [0,]1,2,3,...,999999999,1000000000
    // we cannot use an array as it would need to be 4*1000000000 (or at least
    // using memory efficient indexing 2*1000000000) which exceeds memory limit,
    // we will use a map instead, the constraints of the problem would in the worst
    // case have 100000 ranges occupied.
    unordered_map<int,int> t; // segment tree

    // range update
    void update(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return;

        // number of nodes in this range
        int n = tr-tl+1;
        if( t[v] == n ) // entire range had been covered earlier
            return;

        if (l == tl && r == tr) {
            t[v] = n;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm));
            update(v*2+1, tm+1, tr, max(l, tm+1), r);
            t[v] = t[v*2]+t[v*2+1];
        }
    }


public:
    CountIntervals() {
    }

    void add(int left, int right) {
        update(1,0,1000000000,left,right);
    }

    int count() {
        return t[1]; // root of our segment tree
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
