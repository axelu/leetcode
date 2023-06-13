
// 2516. Take K of Each Character From Left and Right
// https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/


class Solution {
private:
    bool solve(int t, int k, int n, int prefixSum_a[], int prefixSum_b[], int prefixSum_c[]) {
        // cout << "solve t " << t << endl;

        for(int i = t; i >= 0; --i) {
            // count of letters a, b, c in range [0,i] inclusive
            int lft_a = prefixSum_a[i];
            int lft_b = prefixSum_b[i];
            int lft_c = prefixSum_c[i];

            // count of letters a, b, c in range [,n-1] inclusive
            int j = n - (t-i);
            int rgt_a = prefixSum_a[n] - prefixSum_a[j];
            int rgt_b = prefixSum_b[n] - prefixSum_b[j];
            int rgt_c = prefixSum_c[n] - prefixSum_c[j];

            if( lft_a + rgt_a >= k && lft_b + rgt_b >= k && lft_c + rgt_c >= k )
                return true;
        }

        return false;
    }

    // binary search
    int search(int s, int e, int k, int n, int prefixSum_a[], int prefixSum_b[], int prefixSum_c[]) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        bool f = solve(mid,k,n,prefixSum_a,prefixSum_b,prefixSum_c);
        if( f ) {
            // can we do better?
            int t = search(s,mid-1,k,n,prefixSum_a,prefixSum_b,prefixSum_c);
            return t != -1 ? t : mid;
        }
        return search(mid+1,e,k,n,prefixSum_a,prefixSum_b,prefixSum_c);
    }

public:
    int takeCharacters(string s, int k) {
        if( k == 0 )
            return 0;

        int n = s.size();
        if( n < k * 3 )
            return -1;

        int prefixSum_a[n+1];
        prefixSum_a[0] = 0;
        int prefixSum_b[n+1];
        prefixSum_b[0] = 0;
        int prefixSum_c[n+1];
        prefixSum_c[0] = 0;

        for(int i = 1; i <= n; ++i) {
            if( s[i-1] == 'a' ) {
                prefixSum_a[i] = prefixSum_a[i-1] + 1;
                prefixSum_b[i] = prefixSum_b[i-1];
                prefixSum_c[i] = prefixSum_c[i-1];
            } else if( s[i-1] == 'b' ) {
                prefixSum_a[i] = prefixSum_a[i-1];
                prefixSum_b[i] = prefixSum_b[i-1] + 1;
                prefixSum_c[i] = prefixSum_c[i-1];
            } else { // s[i-1] == 'c'
                prefixSum_a[i] = prefixSum_a[i-1];
                prefixSum_b[i] = prefixSum_b[i-1];
                prefixSum_c[i] = prefixSum_c[i-1] + 1;
            }
        }

        if( prefixSum_a[n] < k || prefixSum_b[n] < k || prefixSum_c[n] < k )
            return -1;

        return search(k*3,n,k,n,prefixSum_a,prefixSum_b,prefixSum_c);
    }
};
