
// 76. Minimum Window Substring
// https://leetcode.com/problems/minimum-window-substring/





class Solution {
private:
    // debug
    void printCnt(int A[]) {
        // debug
        for(int i = 0; i < 52; ++i) {
            char c;
            if( i < 26 ) c = i+'a';
            else c = i-26+'A';
            cout << c << ":" << A[i] <<  " ";

        }
        cout << endl;
    }

    bool isSubstring(int A[], int B[]) {
        for(int i = 0; i < 52; ++i)
            if( B[i] != 0 && A[i] < B[i] )
                return false;
        return true;
    }

public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        if( n > m )
            return "";

        int cntT[52]; memset(cntT,0,sizeof cntT); // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
        for(int i = 0; i < n; ++i)
            if( t[i] >= 97 ) ++cntT[t[i]-'a'];
            else ++cntT[t[i]-'A'+26];
        // printCnt(cntT);

        int ans = INT_MAX;
        // best possible answer is n

        int cntS[52]; memset(cntS,0,sizeof cntS); // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
        int  l;
        int ir = -1;                 // index in s at which our best answer starts
        int  i = 0;                  // left idx
        for(int j = 0; j < m; ++j) { // right idx
            // cout << "i:" << i << " j:" << j << endl;

            if( s[j] >= 97 ) ++cntS[s[j]-'a'];
            else ++cntS[s[j]-'A'+26];

            l = j-i+1;
            if( l < n || !isSubstring(cntS,cntT) )
                continue;

            // sliding window
            while( l >= n && isSubstring(cntS,cntT) ) {
                if( l == n )
                    return s.substr(i,n);

                if( l < ans ) {
                    ans = l;
                    ir = i;
                }

                if( s[i] >= 97 ) --cntS[s[i]-'a'];
                else --cntS[s[i]-'A'+26];
                ++i;
                l = j-i+1;
            }
        }

        return ans == INT_MAX ? "" : s.substr(ir,ans);
    }
};
