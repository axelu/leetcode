
// 2712. Minimum Cost to Make All Characters Equal
// https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/




class Solution {
public:
    long long minimumCost(string s) {
        int n = s.size();
        if( n == 1 )
            return 0;

        // left to right
        long long l2r[n];
        long long last0 = 0;
        long long last1 = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                l2r[i] = i + 1 + last1;
                last0 = l2r[i];
            } else { // s[i] == '1'
                l2r[i] = i + 1 + last0;
                last1 = l2r[i];
            }
        }
        // edge case
        if( l2r[n-1] == n )
            return 0;
        /*
        cout << "l2r" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << l2r[i] << " ";
        cout << endl;
        */

        // right to left
        long long r2l[n];
        last0 = 0;
        last1 = 0;
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == '0' ) {
                r2l[i] = n - i + last1;
                last0 = r2l[i];
            } else { // s[i] == '1'
                r2l[i] = n - i + last0;
                last1 = r2l[i];
            }
        }
        /*
        cout << "r2l" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << r2l[i] << " ";
        cout << endl;
        */

        long long ans = LLONG_MAX;
        // left to right
        last0 = -1; // idx
        last1 = -1; // idx
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                // left cost to convert from the last 0 seen
                long long l = 0;
                if( last0 != -1 )
                    l = l2r[last0];
                ans = min(ans, l + r2l[i]);
                last0 = i;

            } else { // s[i] == '1'
                long long l = 0;
                if( last1 != -1 )
                    l = l2r[last1];
                ans = min(ans, l + r2l[i]);
                last1 = i;
            }
        }

        // right to left
        last0 = -1; // idx
        last1 = -1; // idx
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == '0' ) {
                // left cost to convert from the last 0 seen
                long long r = 0;
                if( last0 != -1 )
                    r = r2l[last0];
                ans = min(ans, l2r[i] + r);
                last0 = i;

            } else { // s[i] == '1'
                long long r = 0;
                if( last1 != -1 )
                    r = r2l[last1];
                ans = min(ans, l2r[i] + r);
                last1 = i;
            }
        }

        return ans;
    }
};
