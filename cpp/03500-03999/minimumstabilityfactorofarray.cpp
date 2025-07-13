
// 3605. Minimum Stability Factor of Array
// https://leetcode.com/problems/minimum-stability-factor-of-array/


class Solution {
private:
    // recursive function to return gcd of a and b
    int gcd(int a, int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    int t[400000]; // segment tree Greatest Common Divisor (GCD), range query

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = gcd(t[v*2], t[v*2+1]);
        }
    }

    int get_gcd(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -1;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;

        int gcd_l = get_gcd(v*2, tl, tm, l, min(r, tm));
        int gcd_r = get_gcd(v*2+1, tm+1, tr, max(l, tm+1), r);
        if( gcd_l == -1 )
            return gcd_r;
        if( gcd_r == -1 )
            return gcd_l;
        return gcd(gcd_l, gcd_r);
    }

    int solve(int n, int l) {
        // counts the windows with size l that have a gcd > 1
        int cnt = 0;
        for(int i = 0; i <= n-l;) {
            int _gcd = get_gcd(1, 0, n-1, i, i+l-1);
            if( _gcd > 1 ) {
                ++cnt;
                // we can advance to i + l
                i += l;
            } else {
                ++i;
            }
        }
        return cnt;
    }

    // binary search
    // seach for each window with given length (mid)
    // counting the number of windows that have a gcd > 1
    // if that count <= maxC, then we can break all those and smaller,
    // otherwise increase window size
    int search(int n, int s, int e, int maxC) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int count = solve(n, mid);
        if( count <= maxC ) {
            // can we do better?
            // can we make our window size smaller?
            int t = search(n, s, mid-1, maxC);
            return t != -1 ? t : mid;
        }
        return search(n, mid+1, e, maxC);
    }


public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();

        // edge case maxC = n
        // then we can set each nums[i] to 1
        if( maxC == n )
            return 0;

        build(nums, 1, 0, n-1);

        int ans = search(n, 1, n, maxC) - 1;
        return ans >= 0 ? ans : n;
    }
};
