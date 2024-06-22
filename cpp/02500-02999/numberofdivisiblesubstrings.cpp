
// 2950. Number of Divisible Substrings
// https://leetcode.com/problems/number-of-divisible-substrings/




class Solution {
public:
    int countDivisibleSubstrings(string word) {
        int n = word.size(); // 1 <= word.length <= 2000

        int ans = 0;

        int mp[26];
        mp[0]  = 1; // a
        mp[1]  = 1; // b
        mp[2]  = 2; // c
        mp[3]  = 2; // d
        mp[4]  = 2; // e
        mp[5]  = 3; // f
        mp[6]  = 3; // g
        mp[7]  = 3; // h
        mp[8]  = 4; // i
        mp[9]  = 4; // j
        mp[10] = 4; // k
        mp[11] = 5; // l
        mp[12] = 5; // m
        mp[13] = 5; // n
        mp[14] = 6; // o
        mp[15] = 6; // p
        mp[16] = 6; // q
        mp[17] = 7; // r
        mp[18] = 7; // s
        mp[19] = 7; // t
        mp[20] = 8; // u
        mp[21] = 8; // v
        mp[22] = 8; // w
        mp[23] = 9; // x
        mp[24] = 9; // y
        mp[25] = 9; // z

        // Brute Force

        int t[n];memset(t,0,sizeof t); // sum of substring starting at i
        for(int l = 1; l <= n; ++l) {
            for(int i = 0; i <= n-l; ++i) {
                int j = i + l - 1;
                t[i] += mp[word[j]-'a'];
                if( t[i] % l == 0 )
                    ++ans;
            }
        }

        return ans;
    }
};
