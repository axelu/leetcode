
// 1960. Maximum Product of the Length of Two Palindromic Substrings
// https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/





class Solution {
private:
    // Manacher's Algorithm - Finding all sub-palindromes
    // https://cp-algorithms.com/string/manacher.html
    vector<int> manacher_odd(string& s) {
        int n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);
        int l = 1, r = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while(s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
    }

public:
    long long maxProduct(string s) {
        int n = s.size(); // cout << "n " << n << endl; // 2 <= s.length <= 1e5
        vector<int> odd = manacher_odd(s);
        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << odd[i] << " ";
        cout << endl;
        */

        int tr[n];memset(tr,0,sizeof tr);
        int tl[n];memset(tl,0,sizeof tl);
        for(int i = 0; i < n; ++i) {
            int lft = i - (odd[i] - 1); // start of the longest palindrom centered around i
            int rgt = i + (odd[i] - 1); // end of the longest palindrome centered around i
            int lgt = rgt - lft + 1;    // same as (odd[i] * 2) - 1;

            tr[lft] = max(tr[lft], lgt);
            tl[rgt] = max(tl[rgt], lgt);
        }
        /*
        cout << "tr before" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << tr[i] << " ";
        cout << endl;
        cout << "tl before" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << tl[i] << " ";
        cout << endl;
        */

        // post processing tr
        for(int i = 1; i < n; ++i) {
            if( tr[i] < tr[i-1] - 2 )
                tr[i] = tr[i-1] - 2;
        }
        /*
        cout << "tr after" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << tr[i] << " ";
        cout << endl;
        */

        // post processing tl
        for(int i = n-2; i >= 0; --i) {
            if( tl[i] < tl[i+1] - 2 )
                tl[i] = tl[i+1] - 2;
        }
        /*
        cout << "tl after" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << tl[i] << " ";
        cout << endl;
        */

        // right to left record max palindrome length to the right of and including i
        long long r2l[n];
        r2l[n-1] = 1LL;
        for(int i = n-2; i >= 0; --i)
            r2l[i] = max(r2l[i+1], (long long)tr[i]);
        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << r2l[i] << " ";
        cout << endl;
        */

        // left to right
        long long ans = 1LL;
        long long mxl = 1LL;
        for(int i = 0; i < n-1; ++i) {
            mxl = max(mxl, (long long)tl[i]);
            ans = max(ans, mxl * r2l[i+1]);
        }

        return ans;
    }
};
