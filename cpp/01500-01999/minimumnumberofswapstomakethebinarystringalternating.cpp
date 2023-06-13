
// 1864. Minimum Number of Swaps to Make the Binary String Alternating
// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/



class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();

        int cnt0even = 0, cnt0odd = 0;
        int cnt1even = 0, cnt1odd = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                if( i % 2 == 0 )
                    ++cnt0even;
                else
                    ++cnt0odd;
            } else {
                if( i % 2 == 0 )
                    ++cnt1even;
                else
                    ++cnt1odd;
            }
        }

        int cnt0 = cnt0even +cnt0odd;
        int cnt1 = cnt1even +cnt1odd;
        if( n % 2 == 0 && cnt0 != cnt1 )
            return -1;
        if( n % 2 == 1 && cnt0 != n/2 && cnt1 != n/2 )
            return -1;

        if( n % 2 == 0 ) {
            // in the end, we either need
            //   all 0s on even and all 1s on odd OR
            //   all 0s on odd  and all 1s on even
            return min(n/2 - cnt0odd, n/2 - cnt0even); // equvalent min(n/2 - cnt1odd, n/2 - cnt1even)
        }

        // remaining case: odd with solution
        // whatever we have more off needs to go on even indicies
        return cnt0 > cnt1 ? (n/2 + 1) - cnt0even : (n/2 + 1) - cnt1even;

    }
};
