
// 1930. Unique Length-3 Palindromic Subsequences
// https://leetcode.com/problems/unique-length-3-palindromic-subsequences/
// https://leetcode.com/contest/weekly-contest-249/problems/unique-length-3-palindromic-subsequences/





class Solution {
private:
    void printBinary(int x) {
        for(int i = 31; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }
    
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int query(int b[], int len, int l, int r, string& s) {
        int t = 0;

        int c_l = l/len; // index of left block
        int c_r = r/len; // index of right block

        if( c_l == c_r )
            for(int i = l; i <= r; ++i)
                t |= 1 << (s[i]-'a');

        else {
            for(int i = l, end = (c_l+1)*len-1; i<=end; ++i)
                t |= 1 << (s[i]-'a');

            for(int i= c_l+1; i <= c_r-1; ++i)
                t |= b[i];

            for(int i = c_r*len; i <= r; ++i)
                t |= 1 << (s[i]-'a');
        }
        
        return countSetBits(t);
    }
    
public:
    int countPalindromicSubsequence(string& s) {
        int n = s.size();

        int ans = 0;
         
        // idea
        // record 1st and last occurrence of each char
        // let l be the left most occurence of char
        // let r be the right most occurence of char
        // for every char if r-l >= 2
        // query range [l+1,r-1] for OR  
        // add set bit count for OR result to ans
        
        // square root decomposition
        int len = (int) sqrt(n + .0) + 1; // block size and number of blocks
        int b[len];memset(b,0,sizeof b);
        
        int l[26];memset(l,-1,sizeof l);
        int r[26];
        
        int c;
        for(int i = 0; i < n; ++i) {
            c = s[i]-'a';

            if( l[c] == -1 )
                l[c] = i;            
            r[c] = i;
            b[i/len] |= 1 << c;
        }
        
        for(int i = 0; i < 26; ++i)
            if( l[i] != -1 && r[i]-l[i] >= 2 )
                ans += query(b,len,l[i]+1,r[i]-1,s);
        
        return ans;
    }
};
