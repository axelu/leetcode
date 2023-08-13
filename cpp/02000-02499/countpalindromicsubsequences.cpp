
// 2484. Count Palindromic Subsequences
// https://leetcode.com/problems/count-palindromic-subsequences/





class Solution {
public:
    int countPalindromes(string s) {
        int n = s.size();
        if( n < 5 )
            return 0;
        if( n == 5 )
            return s[0] == s[4] && s[1] == s[3];

        // left to right
        int cntl2r[n][10]; // count of integers 0 to 9 to the left of i
        memset(cntl2r,0,sizeof cntl2r);
        unordered_map<int,long> mpl2r[n];
        for(int i = 1; i < n; ++i) {
            for(int k = 0; k < 10; ++k)
                cntl2r[i][k] = cntl2r[i-1][k];
            ++cntl2r[i][s[i-1]-'0'];

            mpl2r[i] = mpl2r[i-1];
            int curr = s[i]-'0';
            for(int j = 0; j < 10; ++j) {
                int key = j*10 + curr;
                mpl2r[i][key] += cntl2r[i][j];
            }
        }
        // debug
        /*
        for(int k = 0; k < 10; ++k) {
            for(int i = 0; i < n; ++i)
                cout << cntl2r[i][k] << " ";
            cout << endl;
        }
        */

        // right to left
        int cntr2l[n][10]; // count of integers 0 to 9 to the right of i
        memset(cntr2l,0,sizeof cntr2l);
        unordered_map<int,long> mpr2l[n];
        for(int i = n-2; i >= 0; --i) {
            for(int k = 0; k < 10; ++k)
                cntr2l[i][k] = cntr2l[i+1][k];
            ++cntr2l[i][s[i+1]-'0'];

            mpr2l[i] = mpr2l[i+1];
            int curr = s[i]-'0';
            for(int j = 0; j < 10; ++j) {
                int key = curr*10 + j;
                mpr2l[i][key] += cntr2l[i][j];
            }
        }

        long mod = 1000000007;
        long ans = 0;
        for(int i = 2; i < n-2; ++i) {
            for(auto it = mpl2r[i-1].begin(); it != mpl2r[i-1].end(); ++it) {
                int keyl2r = it->first;
                int keyr2l = ((keyl2r % 10) * 10) + (keyl2r / 10);
                auto f = mpr2l[i+1].find(keyr2l);
                if( f != mpr2l[i+1].end() )
                    ans = (ans + ( it->second * f->second)) % mod;
            }
        }

        return ans;
    }
};
