
// 1482. Minimum Number of Days to Make m Bouquets
// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/




class Solution {
private:
    int * blooming;

    bool canMakeBouquets(vector<int>& bloomDay, int n, int days, int m, int k) {
        // can we make m bouquets that require k **adjacent** flowers in 'days' days?

        int c = 0;     // number of continues flowers
        int total = 0; // number of bouquets made
        for(int i = 0; i < n && total < m; ++i) {
            if( bloomDay[i] <= days )
                ++c;
            else
                c = 0; // the current flower is not blooming yet
            if( c == k ) {
                c = 0;
                ++total;
            }
        }

        return total == m;
    }

    // binary search
    int search(vector<int>& bloomDay, int n, int s, int e, int m, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = canMakeBouquets(bloomDay,n,mid,m,k);
        if( f ) {
            // can we do better?
            int t = search(bloomDay,n,s,mid-1,m,k);
            return t != -1 ? t : mid;
        } else {
            return search(bloomDay,n,mid+1,e,m,k);
        }
    }

public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        // m = number of bouquets to make.
        // k = number of **adjacent** flowers needed to make a bouquet

        int n = bloomDay.size(); // number of flowers
        if( m * k > n )
            return -1;

        int mx = INT_MIN;
        int mn = INT_MAX;
        for(int i = 0; i < n; ++i) {
            mx = max(mx,bloomDay[i]);
            mn = min(mn,bloomDay[i]);
        }

        if( m * k == n ) // all flowers must bloom
            return mx;

        // it will take at least mn day and max mx days
        return search(bloomDay,n,mn,mx,m,k);
    }
};
