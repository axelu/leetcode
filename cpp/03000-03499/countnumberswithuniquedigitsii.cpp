
// 3032. Count Numbers With Unique Digits II
// https://leetcode.com/problems/count-numbers-with-unique-digits-ii/




class Solution {
public:
    int numberCount(int a, int b) {
        int ans = b - a + 1;
        for(int i = a; i <= b; ++i) {
            int cnt[10];memset(cnt,0,sizeof cnt);
            int x = i;
            while( x ) {
                int rem = x % 10;
                if( ++cnt[rem] == 2 ) {
                    --ans;
                    break;
                }
                x /= 10;
            }
        }
        return ans;
    }
};
