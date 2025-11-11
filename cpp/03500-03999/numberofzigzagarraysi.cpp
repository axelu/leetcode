
// 3699. Number of ZigZag Arrays I
// https://leetcode.com/problems/number-of-zigzag-arrays-i/



class Solution {
private:
    long const mod = 1000000007;
public:
    int zigZagArrays(int n, int l, int r) {

        // brute force
        int d = r - l;

        long _pre[2000]; long * pre = _pre;
        long _cur[2000]; long * cur = _cur;

        // left to right
        for(int j = 0; j < d; ++j)
            pre[j] = j+1;

        /*
        // debug
        for(int j = 0; j < d; ++j)
            cout << pre[j] << " ";
        cout << endl;
        */

        for(int i = 1; i < n; ++i) {
            if( i % 2 ) { // right to left
                cur[d-1] = pre[d-1];
                for(int j = d-2; j >= 0; --j) {
                    cur[j] = pre[j] + cur[j+1];
                    if( cur[j] > mod )
                        cur[j] -= mod;
                }

            } else { // left to right
                cur[0] = pre[0];
                for(int j = 1; j < d; ++j) {
                    cur[j] = cur[j-1] + pre[j];
                    if( cur[j] > mod )
                        cur[j] -= mod;
                }
            }

            /*
            // debug
            for(int j = 0; j < d; ++j)
                cout << cur[j] << " ";
            cout << endl;
            */

            swap(pre,cur);
        }

        return n % 2 ? (pre[d-1] * 2L) % mod : (pre[0] * 2L) % mod;
    }
};
