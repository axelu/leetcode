
// 2896. Apply Operations to Make Two Strings Equal
// https://leetcode.com/problems/apply-operations-to-make-two-strings-equal/




class Solution {
private:
    int mem[500][2];

    int rec(string& s1, string& s2, int n, int pos, int used_x, int x) {
        // cout << "rec pos " << pos << " used_x " << used_x << endl;
        if( pos == n )
            return used_x ? 300000 : 0;

        if( mem[pos][used_x] != -1 )
            return mem[pos][used_x];

        int ret = 300000; // arbitrarily large number

        if( s1[pos] != s2[pos] ) {
            // handle us being at pos == n-1
            if( pos == n-1 && used_x == 0 )
                return ret;

            // we have a choice
            //    flip pos and pos+1 for the cost of 1 OR
            //    flip pos*
            //    * if we flip pos, we either can take advantage of
            //      an earlier pos given us a credit (used_x) OR
            //      we need to do it for the cost of x communicating downstream
            //      that a later position can be flipped for 'no' cost as we
            //      already accounted for the cost at the current pos

            // flip pos and pos+1
            //     no need to flip current pos as we only move forward
            s1[pos+1] = s1[pos+1] == '1' ? '0' : '1';
            int a = 1 + rec(s1,s2,n,pos+1,used_x,x);
            // backtrack
            s1[pos+1] = s1[pos+1] == '1' ? '0' : '1';

            int b = 300000;
            if( used_x )
                b = rec(s1,s2,n,pos+1,0,x);
            else
                b = x + rec(s1,s2,n,pos+1,1,x);

            ret = min(a,b);

        } else {
            // just passing through
            ret = rec(s1,s2,n,pos+1,used_x,x);
        }

        return mem[pos][used_x] = ret;
    }

public:
    int minOperations(string s1, string s2, int x) {
        int n = s1.size(); // n == s1.length == s2.length

        memset(mem,-1,sizeof mem);
        int ans = rec(s1,s2,n,0,0,x);
        return ans < 300000 ? ans : -1;
    }
};
