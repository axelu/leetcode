
// 3707. Equal Score Substrings
// https://leetcode.com/problems/equal-score-substrings/



class Solution {
public:
    bool scoreBalance(string s) {
        int n = s.size();

        int prefixSum[101];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + ((s[i-1] - 'a') + 1);

        for(int i = 0; i < n; ++i) {
            // a = sum 0..i
            int a = prefixSum[i+1];
            // b = sum i+1..n-1
            int b = prefixSum[n] - a;

            if( a == b )
                return true;
        }

        return false;
    }
};
