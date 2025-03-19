
// 2790. Maximum Number of Groups With Increasing Length
// https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/

// great explanation
// https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/solutions/4196962/three-approaches-everyone-can-understand/





class Solution {
private:
    bool canForm(vector<int>& usageLimits, int m) {
        // usageLimits is sorted desc
        // we move from left to right in usageLimits
        // the index in usageLimits represents the row we are on
        // row 0 needs have a length respectively height of m
        // row 1 needs to have a length respectively height of m-1
        // and so on
        // example [5,5,5,4,4,4]
        //
        // group 0 ->                  2\
        // group 1 -> 0 1 2            0 1\
        // group 2 -> 0 1 2 3 4 5      0 1 2\3 4 5
        // group 3 -> 0 1 2 3 4 5      0 1 2 3\4 5
        // group 4 -> 0 1 2 3 4 5      0 1 2 3 4\5
        // group 5 -> 0 1 2 3 4 5      0 1 2 3 4 5\
        // index      0 1 2 3 4 5
        // if we don't have enough, we record a deficit
        // if we have to many, we satisfy the deficit, because
        // we can move excess to the left w/o violating the constraint
        // if we end with a deficit of 0, we can make it and return true

        int deficit = 0;
        for(int x: usageLimits) {
            if( m == 0 && deficit == 0 )
                return true;

            if( x > m && deficit < 0 )
                deficit = min(0, deficit + (x-m));

            if( x < m )
                deficit = deficit - (m-x);

            m = max(m-1,0);
        }

        return deficit == 0;
    }

    // binary search
    int search(vector<int>& usageLimits, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( canForm(usageLimits, mid) ) {
            // can we do better?
            int t = search(usageLimits, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(usageLimits, s, mid-1);
    }

public:
    int maxIncreasingGroups(vector<int>& usageLimits) {
        int n = usageLimits.size(); // 1 <= n <= 1e5

        // our max ans cannot be larger than n because of the constraint
        // that each group must consist of distinct numbers.

        sort(begin(usageLimits), end(usageLimits), greater<int>());
        return search(usageLimits, min(usageLimits.back(), n), n);
    }
};
