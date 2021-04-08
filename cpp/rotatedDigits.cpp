
// 788. Rotated Digits
// https://leetcode.com/problems/rotated-digits/



class Solution {
private:
    int rotateDigits(int N) {
        // digit rotation rules
        // 0 -> 0
        // 1 -> 1
        // 2 -> 5
        // 3 -> invalid
        // 4 -> invalid
        // 5 -> 2
        // 6 -> 9
        // 7 -> invalid
        // 8 -> 8
        // 9 -> 6
        int rem;
        int X = 0;
        int f = 1;
        while(N>0) {
            rem = N % 10;
            if( rem == 3 || rem == 4 || rem == 7 ) return -1;
            if( rem == 2 ) rem = 5;
            else if( rem == 5 ) rem = 2;
            else if( rem == 6 ) rem = 9;
            else if( rem == 9 ) rem = 6;
            X += rem*f;
            N /= 10;
            f *= 10;
        }
        return X;
    }

public:
    int rotatedDigits(int N) {
        if( N == 1 ) return 0;

        int ans = 0;
        int X;
        for(int i = 2; i <= N; ++i) {
            X = rotateDigits(i);
            if( X != -1 && X != i ) ++ans;
        }
        return ans;
    }
};
