
// 3721. Longest Balanced Subarray II
// https://leetcode.com/problems/longest-balanced-subarray-ii/





/* idea
 * we will go through nums from left to right
 * we will update a running count of odds and evens from
 * right to left, including the difference of odds-evens
 *   update: as we actually don't need to odds and evens, we only update diff odds-evens, read on
 * we will use a segment tree to quickly make range updates
 * encountering an even update diff odds-evens by -1
 * encountering an odd, update diff odds-evens by +1
 * let us assume we are at pos j, and nums[j] was last seen at index i
 * the update only applies to range [i+1,j] !!!
 * then we search for the left most occurance of diff == 0
 * the diff values from one position to the next can only differ by +/- 1
 * hence we will look for min <= 0 && max >= 0 and traverse left in our tree if found
 */

class Solution {
private:
    // segment tree, min and max, range update, search for left most 0 (increasing/decreasing by 1)
    pair<int,int> t[400000];
    int lazy[400000];

    pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        int mn = min(a.first,b.first);
        int mx = max(a.second,b.second);
        return make_pair(mn,mx);
    }

    void push(int v) {
        t[v*2].first += lazy[v];
        t[v*2].second += lazy[v];
        lazy[v*2] += lazy[v];

        t[v*2+1].first += lazy[v];
        t[v*2+1].second += lazy[v];
        lazy[v*2+1] += lazy[v];

        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v].first += addend;
            t[v].second += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = combine(t[v*2],t[v*2+1]);
        }
    }

    // find the smallest i in the range [l...r], such that a[i] is 0
    int get_first(int v, int tl, int tr, int l, int r) {
        if(tl > r || tr < l) return -1;

        push(v);

        if( t[v].first > 0 || t[v].second < 0) return -1;

        if (tl == tr) return tl;

        int tm = tl + (tr-tl)/2;
        int left = get_first(2*v, tl, tm, l, r);
        if(left != -1) return left;
        return get_first(2*v+1, tm+1, tr, l ,r);
    }

public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5
        if( n == 1 )
            return 0;

        int ans = 0;

        // segment tree holding the diff odds - evens
        // init tree to all 0's => pair will be init to {0,0}
        memset(lazy, 0, sizeof lazy);

        // position when we saw a given value last
        int last_seen[100001]; memset(last_seen, -1, sizeof last_seen);

        for(int j = 0; j < n; ++j) {
            int i = last_seen[nums[j]];
            bool is_odd = nums[j] % 2;
            int addend = is_odd ? 1 : -1;
            update(1, 0, n-1, i+1, j, addend);
            last_seen[nums[j]] = j;

            // index of left most position in range 0...j where odds-evens = 0;
            // if there is none, then a == -1
            int a = get_first(1, 0, n-1, 0, j); // index
            // cout << "j " << j << " a " << a << endl;
            if( a != -1 )
                ans = max(ans, j-a+1);
        }

        return ans;
    }
};
