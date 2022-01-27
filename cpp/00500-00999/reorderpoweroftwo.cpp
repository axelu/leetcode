
// 869. Reordered Power of 2
// https://leetcode.com/problems/reordered-power-of-2/
// day 21 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3679/




/*
2^0  1
2^1  2
2^2  4
2^3  8
2^4  16
2^5  32
2^6  64
2^7  128
2^8  256
2^9  512
2^10 1024
2^11 2048
2^12 4096
2^13 8192
2^14 16384
2^15 32768
2^16 65536
2^17 131072
2^18 262144
2^19 524288
2^20 1048576
2^21 2097152
2^22 4194304
2^23 8388608
2^24 16777216
2^25 33554432
2^26 67108864
2^27 134217728
2^28 268435456
2^29 536870912
2^30 1073741824
2^31 2147483648
*/
class Solution {
public:
    bool reorderedPowerOf2(int N) {
        int nbrDigits = 0;
        int cnt[10]; memset(cnt,0,sizeof cnt);

        while(N>0) {
            ++cnt[N % 10];
            N /= 10;
            ++nbrDigits;
        }

        vector<int> pow2[11];
        pow2[1] = {1,2,4,8};
        pow2[2] = {16,32,64};
        pow2[3] = {128,256,512};
        pow2[4] = {1024,2048,4096,8192};
        pow2[5] = {16384,32768,65536};
        pow2[6] = {131072,262144,524288};
        pow2[7] = {1048576,2097152,4194304,8388608};
        pow2[8] = {16777216,33554432,67108864};
        pow2[9] = {134217728,268435456,536870912};


        int digits[10];
        int x,rem;
        bool f;
        for(int i = 0; i < pow2[nbrDigits].size(); ++i) {
            copy(cnt,cnt+10,digits);
            x = pow2[nbrDigits][i];

            f = true;
            while(x>0) {
                rem = x%10;
                if( digits[rem] == 0 ) {
                    f = false;
                    break;
                }
                --digits[rem];
                x /= 10;
            }
            if( f ) return true;
        }
        return false;
    }
};
