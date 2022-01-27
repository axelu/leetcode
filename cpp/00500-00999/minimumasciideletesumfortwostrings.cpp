
// 712. Minimum ASCII Delete Sum for Two Strings
// https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/


class Solution {
private:
    int mem[1001][1001];


    int rec(string& s1, int n1, int i, string& s2, int n2, int j) {
        if( i == n1 && j == n2 )
            return 0;

        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 0;

        if( i == n1 ) {
            for(int k = j; k < n2; ++k)
                ret += s2[k];

        } else if( j == n2 ) {
            for(int k = i; k < n1; ++k)
                ret += s1[k];

        } else if( s1[i] == s2[j] ) {
            ret = rec(s1,n1,i+1,s2,n2,j+1);

        } else {
            // we have a choice
            // advance in s1 (delete current char from s1)
            int a = s1[i] + rec(s1,n1,i+1,s2,n2,j);
            // advance in s2 (delete current char from s2)
            int b = s2[j] + rec(s1,n1,i,s2,n2,j+1);

            ret = min(a,b);
        }

        return mem[i][j] = ret;
    }

public:
    int minimumDeleteSum(string& s1, string& s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        memset(mem,-1,sizeof mem);
        return rec(s1,n1,0,s2,n2,0);
    }
};
