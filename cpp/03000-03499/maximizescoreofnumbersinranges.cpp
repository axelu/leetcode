
// 3281. Maximize Score of Numbers in Ranges
// https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/





class Solution {
private:

    bool solve(vector<int>& start, int d, int i, long pos, int mn) {
        int n = start.size();
        if( i == n )
            return true;

        // we need to be able to reach interval i from pos by not jumping less than mn
        // meaning we cannot overshoot

        int s = start[i];
        long e = s + d;

        if( pos + mn > e )
            return false;

        int pos_new = pos + mn >= s ? pos + mn : s;
        return solve(start, d, i+1, pos_new, mn);
    }

    // binary search
    int search(vector<int>& start, int d, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(start, d, 1, start[0], mid);
        if( f ) {
            // can we do better?
            int t = search(start, d, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(start, d, s, mid-1);
    }

public:
    int maxPossibleScore(vector<int>& start, int d) {
        int n = start.size();

        sort(start.begin(), start.end(), [d](int a, int b) {
            int aend = a + d;
            int bend = b + d;

            if( a < b ) {
                return true;
            } else if( a == b ) {
                if( aend < bend ) {
                    return true;
                }
            }
            return false;
        });

        // get a min and max
        // two adjacent intervals after sorting
        // abegin bend -> max
        // aend bbegin -> min
        int mx = 0;
        int mn = INT_MAX;
        for(int i = 1; i < n; ++i) {
            int abegin = start[i-1];
            int aend   = abegin + d;
            int bbegin = start[i];
            int bend   = bbegin + d;

            mx = max(mx, bend - abegin);
            mn = min(mn, max(0, bbegin - aend));
        }

        return search(start, d, mn, mx);
    }
};
