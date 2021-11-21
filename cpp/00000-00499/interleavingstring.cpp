
// 97. Interleaving String
// https://leetcode.com/problems/interleaving-string/
// day 2 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/603/week-1-june-1st-june-7th/3765/




class Solution {
private:
    int mem[101][101];

    bool rec(string& s1, string& s2, string& s3, int i, int j, int k) {
        if( mem[i][j] != -1 )
            return mem[i][j];

        bool ret = true;
        if( s1.size() == i ) {          // s1 is exhausted
            int m = j;
            for(; k < s3.size(); ++k) {
                if( s3[k] != s2[m] ) {
                    ret = false;
                    break;
                }
                ++m;
            }
            return mem[i][j] = ret;

        } else if ( s2.size() == j ) {  // s2 is exhausted
            int m = i;
            for(; k < s3.size(); ++k) {
                if( s3[k] != s1[m] ) {
                    ret = false;
                    break;
                }
                ++m;
            }
            return mem[i][j] = ret;

        }

        ret = false;
        if( s1[i] == s3[k] && s2[j] != s3[k] ) {
            // the only path forward is in s1
            ret = rec(s1,s2,s3,i+1,j,k+1);

        } else if( s1[i] != s3[k] && s2[j] == s3[k] ) {
            // the only path forward is in s2
            ret = rec(s1,s2,s3,i,j+1,k+1);

        } else if( s1[i] == s3[k] && s2[j] == s3[k] ) {
            // we can go forward in s1 and in s2
            ret = rec(s1,s2,s3,i+1,j,k+1);
            if( !ret )
               ret = rec(s1,s2,s3,i,j+1,k+1);
        }

        return mem[i][j] = ret;
   }
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if( n1+n2 != n3 ) return false;

        // set starting position i in s1 and j in s2
        // start going through s3 (index k)
        // if s3[k] matches only s1[i], then we can only pull from s1
        // if s3[k] matches only s2[j], then we can only pull from s2
        // if s3[k] matches s1[i] and s2[j], then we need to pursue both path
        // if s3[k] matches neither s1[i] nor s2[j] then we give up on that path

        for(int i = 0; i < 101; ++i)
            for(int j = 0; j < 101; ++j)
                mem[i][j] = -1;
        return rec(s1,s2,s3,0,0,0);
    }
};
