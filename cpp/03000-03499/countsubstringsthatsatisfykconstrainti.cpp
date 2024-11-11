
// 3258. Count Substrings That Satisfy K-Constraint I
// https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/




class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        // 1 <= s.length <= 50
        // small constraint -> brute force

        int n = s.size();

        int ans = 0;

        // optimization:
        //    let l be the length of the substring under investigation
        //    any substring with l <= k does fullfill the condition

        for(int i = 0; i < n; ++i) {
            int sum = 0; // = number of ones in substring
            for(int j = i; j < n; ++j) {
                int l = j - i + 1;
                if( s[j] == '1' )
                    ++sum;

                //  nbr of 1s     nbr of 0s
                //  ---------    ------------
                if( sum <= k  || l - sum <= k )
                    ++ans;
            }
        }

        return ans;
    }
};
