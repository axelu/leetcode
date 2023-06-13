
// 2729. Check if The Number is Fascinating
// https://leetcode.com/problems/check-if-the-number-is-fascinating/




class Solution {
public:
    bool isFascinating(int n) {
        int a = 2 * n;
        if( a > 1000 )
            return false;
        int b = 3 * n;
        if( b > 1000 )
            return false;
        int c = (n * 1000000) + (a * 1000) + b;

        cout << c << endl;

        int cnt[10];memset(cnt,0,sizeof cnt);
        while( c > 0 ) {
            int rem = c % 10;
            if( rem == 0 )
                return false;
            ++cnt[rem];
            if( cnt[rem] > 1 )
                return false;
            c /= 10;
        }
        for(int i = 1; i < 10; ++i)
            if( cnt[i] == 0 )
                return false;

        return true;
    }
};
