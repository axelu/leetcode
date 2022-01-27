
// 926. Flibe Sting to Monotone Increasing
// https://leetcode.com/problems/flip-string-to-monotone-increasing/
// day 10 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3876/



class Solution {
private:
    int rec(string& s, int n, int i, int parent, int mem [][2]) {
        if( i == n )
            return 0;

        if( mem[i][parent] != -1 )
            return mem[i][parent];

        // if parent is 0, then we have choices
        //     - if current is a 0, then leave it OR flip to 1
        //     - if current is a 1, then leave it OR flip to 0
        // if parent is 1, then going forward with a 1 is the only option

        int reta = INT_MAX, retb = INT_MAX;

        if( parent == 0 ) {
            if( s[i] == '0' ) {
                reta = rec(s,n,i+1,0,mem);
                retb = rec(s,n,i+1,1,mem) + 1;
            } else {
                // s[i] == '1'
                reta = rec(s,n,i+1,1,mem);
                retb = rec(s,n,i+1,0,mem) + 1;
            }
        } else {
            // parent == 1
            int add = s[i] == '0' ? 1 : 0;
            reta = rec(s,n,i+1,1,mem) + add;
        }

        return mem[i][parent] = min(reta,retb);
    }
public:
    int minFlipsMonoIncr(string& s) {
        int n = s.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return s[0] == '1' && s[1] == '0';

        int mem[n][2];memset(mem,-1,sizeof mem);
        return rec(s,n,0,0,mem);
    }
};
