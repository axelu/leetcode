
// 390. Elimination Game
// https://leetcode.com/problems/elimination-game/




class Solution {
public:
    int lastRemaining(int n) {
        //   number                     result
        //   elements    direction      s    e     l
        //   ------------------------------------------------------
        //   odd         left to right  s+1  e-1   l/2
        //   even        left to right  s+1  e     l/2
        //   odd         right to left  s+1  e-1   l/2
        //   even        right to left  s    e-1   l/2

        int s = 0;   // 0-indexed
        int e = n-1;
        int dir = 0; // 0 l2r, 1 r2l
        int d = 1;

        while( n > 1 ) {
            // cout << "n " << n << " s " << s << " e " << e << " dir " << dir << endl;
            if( n % 2 ) {
                s += d;
                e -= d;
            } else {
                if( dir )
                    e -= d;
                else
                    s += d;
            }
            n /= 2;
            dir = !dir;
            d *= 2;
        }

        return s+1;
    }
};
