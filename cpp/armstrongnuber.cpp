
// 1134. Armstrong Number
// https://leetcode.com/problems/armstrong-number/


class Solution {
public:
    bool isArmstrong(int N) {
        // 1 <= N <= 10^8
        int n = N;
        stack<int> stck;
        while( n > 0 ) {
            stck.push(n%10);
            n /= 10;
        }

        // max sum from N = 99999999 -> (9^8)*8 = 344373768 < MAX_INT 2147483647, no overflow issue

        int e = stck.size();
        int t = 0;
        while( !stck.empty() ) {
            t += pow(stck.top(),e);
            if( t > N ) return false;
            stck.pop();
        }
        return t == N;
    }
};
