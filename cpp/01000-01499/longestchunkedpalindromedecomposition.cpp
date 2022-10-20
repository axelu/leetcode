
// 1147. Longest Chunked Palindrome Decomposition
// https://leetcode.com/problems/longest-chunked-palindrome-decomposition/




class Solution {
private:
    int p;  // base
public:
    int longestDecomposition(string text) {
        int n = text.size();
        if( n == 1 )
            return 1;

        p = 31;

        // hash starting at index i of length l
        unsigned long long h[n][n+1]; // i,l
        for(int i = 0; i < n; ++i)
            h[i][0] = 0;

        for(int l = 1; l <= n; ++l)
            for(int i = 0; i <= n-l ; ++i)
                h[i][l] = h[i][l-1] * p + (text[i+l-1]-'a'+1);


        int ans = 0;

        int i = 0;
        int j = n-1;
        int l = 1;

        while(true) {
            // cout << "i " << i << " j " << j << " l " << l << endl;

            if( h[i][l] == h[j][l] ) {
                // greedy, shortest match

                // TODO exclude collision

                ans += 2;

                i = i + l;  // advance i
                --j;        // advance j
                l = 1;      // reset l

                if( i == j ) {
                    ++ans;
                    break;
                } else if( i > j ) {
                    break;
                }

            } else {
                --j;
                ++l;

                if( i + l - 1 >= j ) {
                    ++ans;
                    break;
                }
            }
        }

        return ans;
    }
};
