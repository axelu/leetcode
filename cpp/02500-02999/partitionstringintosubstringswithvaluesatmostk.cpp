
// 2522. Partition String Into Substrings With Values at Most K
// https://leetcode.com/problems/partition-string-into-substrings-with-values-at-most-k/



class Solution {
public:
    int minimumPartition(string s, int k) {
        int n = s.size();

        //  s[i] is a digit from '1' to '9'
        //  1 <= k <= 1,000,000,000
        //  as there are only digits 1 to 9
        //  our largest possible substring value is 999,999,999
        //  our largest possible substring length is 9

        int ans = 0;

        // greedily

        int i = 0;                      // right index
        long t = 0;
        for(int j = 0; j < n; ++j) {    // left index
            int digit = s[j] - '0';

            if( digit > k )
                return -1;

            int l = j - i + 1;

            if( digit == k ) {
                if( l > 1 )
                    ++ans;  // finish out prior substring
                ++ans;      // this is another substring
                i = j + 1;
                t = 0;
                continue;
            }

            if( l == 10 ) {
                // we must start a new substring
                ++ans; // finish out prior substring
                i = j;
                l = 1;
                t = 0;
            }

            // calculate value of substring
            t = t * 10 + digit;
            if( t > k ) {
                ++ans; // finish out prior string
                i = j;
                t = digit;
            }
        }
        // finish up
        if( i < n )
            ++ans;

        return ans;
    }
};
