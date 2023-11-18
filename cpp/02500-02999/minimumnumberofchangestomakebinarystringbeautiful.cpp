
// 2914. Minimum Number of Changes to Make Binary String Beautiful
// https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/





class Solution {
private:

    int rec(string& s, int n, int pos, int mem[][2]) {
        // cout << "rec pos " << pos << endl;
        if( pos == n )
            return 0;

        if( pos == n-1 ) // we would need to change the current char
            return 1;

        char c = s[pos];

        if( mem[pos][c-'0'] != -1 )
            return mem[pos][c-'0'];

        int cnt = 0; // count of consecutive c
        int i = pos;
        for( ; i < n; ++i) {
            if( s[i] == c )
                ++cnt;
            else
                break;
        }
        --i;

        // if we are at an uneven count, we have a choice:
        //     change the last char we counted OR
        //     change the next char
        if( cnt % 2 == 1 ) {
            s[i] = s[i] == '1' ? '0' : '1';
            int a = rec(s,n,i,mem);
            // backtrack
            s[i] = s[i] == '1' ? '0' : '1';

            int b = rec(s,n,i+2,mem);

            return mem[pos][c-'0'] = 1 + min(a,b);
        } else {
            return mem[pos][c-'0'] = rec(s,n,i+1,mem);
        }
    }

public:
    int minChanges(string s) {
        int n = s.size(); // n % 2 == 0 iow: n is even

        int mem[n][2];
        memset(mem,-1,sizeof mem);
        return rec(s,n,0,mem);
    }
};
