
// 357. Count Numbers with Unique Digits
// https://leetcode.com/problems/count-numbers-with-unique-digits/


/*
 n = 0 -> 10^0 = 1      0 <= x < 1
 ans = 1  {0}

 n = 1 -> 10^1 = 10     0 <= x < 10
 we know 0..0 inclusive is 1
 we need to figure out 1 <= x <= 9
 there are 9 numbers between 1..9 inclusive
 ans = 1 + 9
 ans = 10 {0,1,2,3,4,5,6,7,8,9}

 n = 2 -> 10^2 = 100     0 <= x < 100
 we know 0..9 inclusive is 10
 we need to figure out 10 <= x <= 99
 there are 90 numbers between 10..99 inclusive,
   9 are not unique 11,22,33,44,55,66,77,88,99
 ans = 10 + (90 - 9*(1)) = 91

 n = 3 -> 10^3 = 1000    0 <= x < 1000
 we know 0..99 inclusive is 91
 we need to figure out 100 <= x <= 999
 there are 900 numbers between 100..999 inclusive
 100x 110x 120  130  ...
 101x 111x 121x 131x
 102  112x 122x 132
 103  113x 123  133x
 104  114x 124  134
 105  115x 125  135
 106  116x 126  136
 107  117x 127  137
 108  118x 128  138
 109  119x 129  139
 ...
 ans = 91 + (900 - 9* (9*2 + 1*10)) = 739

 n = 4 -> 10^4 = 10000   0 <= x < 10000
 we know 0..999 inclusive is 739
 we need to figure out 1000 <= x <= 9999
 there are 9000 numbers between 1000..9999 inclusive
 ans = 739 + (9000 - 9* (9* (8*3 + 2*10) + 1*100))
 ans = 5275

 n = 5 -> 10^5 = 100000   0 <= x < 100000
 we know 0..9999 inclusive is 5275
 we need to figure out 10000 <= x < 99999
 there are 90000 numbers between 10000..99999 inclusive
 ans = 5275 + (90000 - 9* (9* (8* (7*4 + 3*10) + 2*100) + 1*1000))
 ans = 32491

 n = 6 -> 10^6 = 1000000   0 <= x < 1000000
 we know 0..99999 inclusive is 32491
 we need to figure out 100000 <= x < 999999
 there are 900000 numbers between 100000..999999 inclusive
 ans = 32491 + (900000 - 9* (9* (8* (7* (6*5 + 4*10) + 3*100) + 2*1000) + 1*10000))
 ans = 168571

 n = 7 -> 10^7 = 10000000   0 <= x < 10000000
 we know 0..999999 inclusive is 168571
 we need to figure out 1000000 <= x < 9999999
 there are 9000000 numbers between 1000000..9999999 inclusive
 ans = 168571 + (9000000 - 9* (9* (8* (7* (6* (5*6 + 5*10) + 4*100) + 3*1000) + 2*10000) + 1*100000))
 ans = 712891

 n = 8 -> 10^8 = 100000000   0 <= x < 100000000
 we know 0..9999999 inclusive is 712891
 we need to figure out 10000000 <= x < 99999999
 there are 90000000 numbers between 10000000..99999999 inclusive
 ans = 712891 + (90000000 - 9* (9* (8* (7* (6* (5* (4*7 + 6*10) + 5*100) + 4*1000) + 3*10000) + 2*100000) + 1*1000000))
 ans = 2345851


*/
class Solution {
private:
    int rec(int f, int e) {
        if( e == 0 )
            return 1;

        if( e == 1 ) {
            int a = 11-f;
            int b = 10-f;
            return f*a + b*10;
        }

        int b = 10-f;
        return f*rec(f-1,e-1) + b*pow(10,e);
    }
public:
    int countNumbersWithUniqueDigits(int n) {
        int ans = 1;
        if( n == 0 )
            return ans;

        ans = 10;
        if( n == 1 )
            return ans;

        for(int i = 2; i <= n; ++i)
            ans += (9 * pow(10,i-1)) - 9* rec(9,i-2);

        return ans;
    }
};
