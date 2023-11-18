
// 2376. Count Special Integers
// https://leetcode.com/problems/count-special-integers/






/* determining the largest special integer given n
 * example n = 53412
 *             44444
 * example n = 55412
 *             44444
 * example n = 55612
 *             55555
 * example n = 56412
 *             55555
 * example n = 76
 *             66
 * example n = 78
 *             77
 * let cnt be the number of digits in n
 * let the left most digit be at pos 0 and the right most digit at pos cnt-1
 * if there is a digit greather than leftmost more left than a digit less the leftmost,
 * then we can include x composed out completely of leftmost digit
 */
class Solution {
private:
    vector<int> get_cnt(int n) {
        vector<int> ret;
        int rem;
        while( n ) {
            rem = n % 10;
            ret.push_back(rem);
            n /= 10;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

    int mem[2][11][11][1024];

    int rec(int cnt, int pos, int mask, vector<int>& digits, bool mx) {
        // mx is true, if the value left of us was at max
        // in which case we can only go up to max
        if( pos == cnt )
            return 1;

        if( mem[mx][cnt][pos][mask] != -1 )
            return mem[mx][cnt][pos][mask];

        int ret = 0;

        int s = pos == 0 ? 1 : 0;
        int e = 9;
        if( mx )
            e = digits[pos];

        for(int i = s; i <= e; ++i) {
            int mx_new = false;
            if( mx && i == e )
                mx_new = true;
            if( !(mask & (1<<i)) ) {
                // i has not been used so far
                ret += rec(cnt,pos+1,mask|(1<<i),digits,mx_new);
            }
        }

        return mem[mx][cnt][pos][mask] = ret;
    }

public:
    int countSpecialNumbers(int n) {
        if( n < 10 )
            return n; // all the integers from 1 to 9 are special

        vector<int> digits = get_cnt(n);
        int cnt = digits.size();

        // special consideration for the left most pos aka pos 0
        //     we cannot have 0 at pos 0
        //     if include_leftmost
        //         we can go up to leftmost digit, if we reached leftmost, we need to mark
        //             also all digits greater than leftmost as used
        //     else
        //         we can go up to leftmost-1 digit, if we reached leftmost-1, we need to mark
        //             all digits equal and greater than leftmost as used

        int ans = 0;

        memset(mem,-1,sizeof mem);

        for(int l = 1; l < cnt; ++l)
            ans += rec(l,0,0,digits,false);

        ans += rec(cnt,0,0,digits,true);

        return ans;
    }
};
