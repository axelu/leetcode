
// 1397. Find All Good Strings
// https://leetcode.com/problems/find-all-good-strings/





// Knuth–Morris-Pratt (KMP) algorithm
// https://www.scaler.com/topics/data-structures/kmp-algorithm/

class Solution {
private:
    long mod = 1000000007;
    int N;
    char * _s1;
    char * _s2;
    char * _evil; // pattern

    int m;
    int * _LPS;

    vector<int> lps_table(string& pattern) {
        // LPS (longest proper prefix that is also a suffix)
        int m = pattern.size();
        vector<int> LPS(m);
        LPS[0] = 0;  // LPS value of the first element is always 0
        int k = 0;   // length of previous longest proper prefix that is also a suffix
        for(int i = 1; i < m; ++i) {
            while( pattern[i] != pattern[k] && k > 0 )
                k = LPS[k-1];
            if( pattern[i] == pattern[k] )
                LPS[i]=++k;
        }
        return LPS;
    }

    long mem[500][50][2][2];

    long rec(int i, int evil_pos, bool equal_s1, bool equal_s2) {
        // cout << "rec i " << i << " evil_pos " << evil_pos;
        // cout << " equal_s1 " << equal_s1 << " equal_s2 " << equal_s2 << endl;

        // i is position in s1 respectively s2
        // evil_pos is position in evil (our pattern in KMP context)
        // equal_s1  equal_s2
        //   true      true    prior char = s1[i-1] and prior char = s2[i-1]
        //   true      false   prior char = s1[i-1] and prior char < s2[i-1]
        //   false     true    prior char > s1[i-1] and prior char = s2[i-1]
        //   false     false   prior char > s1[i-1] and prior char < s2[i-1] we can use a - z

        if( i == N )
            return 1;

        if( mem[i][evil_pos][equal_s1][equal_s2] != -1 )
            return mem[i][evil_pos][equal_s1][equal_s2];

        // at each position we have a choice to use any lower case char, as long as
        //     we are not building a string smaller than s1
        //     we are not building a string larger than s2
        //     we are not building evil string

        long ret = 0;

        for(char ch = 'a'; ch <= 'z'; ++ch) {
            // if we are walking along the edge of s1,
            // then our current ch has to be be equal or greater than s1[i]
            if( equal_s1 && ch < _s1[i] )
                continue;

            // if we are walking along the edge of s2,
            // then our current ch has to be be smaller or equal than s2[i]
            if( equal_s2 && ch > _s2[i] )
                continue;

            // we must not proceed if we build evil string with the
            // chars that are in our path
            // KMP search
            int j = evil_pos;
            while( _evil[j] != ch && j > 0 )
                j = _LPS[j-1];
            if( _evil[j] == ch ) {
                ++j;
                if( j == m ) // j pointer has reached end of pattern aka evil string
                    continue;
            }

            bool equal_s1_new = equal_s1 && ch == _s1[i];
            bool equal_s2_new = equal_s2 && ch == _s2[i];

            ret = (ret + rec(i+1,j,equal_s1_new,equal_s2_new)) % mod;
        }

        return mem[i][evil_pos][equal_s1][equal_s2] = ret;
    }

public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        m = evil.size();
        vector<int> LPS = lps_table(evil);
        _LPS = LPS.data();

        N = n;              // s1.size() == s2.size() == n
        _s1 = s1.data();    // s1 <= s2
        _s2 = s2.data();
        _evil = evil.data();

        memset(mem,-1,sizeof mem);
        return rec(0,0,true,true);
    }
};
