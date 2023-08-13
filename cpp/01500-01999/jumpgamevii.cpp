
// 1871. Jump Game VII
// https://leetcode.com/problems/jump-game-vii/



class Solution {
private:
    bool rec(string& s, int n, int i, int minJump, int maxJump, int mem[]) {
        // cout << "rec i " << i << endl;
        if( i == n-1 )
           return true;

        if( mem[i] != -1 )
            return mem[i];

        bool ret = false;
        for(int j = min(i + maxJump, n-1); j >= i + minJump; --j) {
            if( s[j] == '1' )
                continue;
            if( rec(s,n,j,minJump,maxJump,mem) ) {
                ret = true;
                break;
            }
        }

        return mem[i] = ret;
    }
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        // cout << "n " << n << endl;

        // pre checks
        if( s[n-1] == '1' )
            return false;
        int mx_consecutive_ones = 0;
        int t = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                mx_consecutive_ones = max(mx_consecutive_ones,t);
                t = 0;
            } else {
                ++t;
            }
        }
        // cout << "mx_consecutive_ones " << mx_consecutive_ones << endl;
        if( mx_consecutive_ones >= maxJump )
            return false;

        int mem[n];memset(mem,-1,sizeof mem);
        return rec(s,n,0,minJump,maxJump,mem);
    }
};
