
// 664. Strange Printer
// https://leetcode.com/problems/strange-printer/


class Solution {
private:
    int mem[100][100];

    int rec(string& str, int i, int j) {
        if( i > j )
        return 0;

        if( i == j )
           return 1;

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we have a choice
        //   print the 1st char only and continue OR
        //   print the 1st char till its next occurence
        //      meaning split the string and calculate the result for both parts

        int a = 1 + rec(str,i+1,j);

        for(int k = i + 1; k <= j; ++k) {
            if( str[k] == str[i] ) {
                int t = rec(str,i,k-1) + rec(str,k+1,j);
                a = min(a,t);
            }
        }
        return mem[i][j] = a;
    }

public:
    int strangePrinter(string s) {
        // it doesn't matter how many of the same char we have adjacent,
        // what matters is the transition
        string str;
        str = s[0];
        for(int i = 1; i < s.size(); ++i)
            if( s[i-1] != s[i] )
                str.push_back(s[i]);

        int n = str.size();

        memset(mem,-1,sizeof mem);
        return rec(str,0,n-1);
    }
};
