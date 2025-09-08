
// 3628. Maximum Number of Subsequences After One Inserting
// https://leetcode.com/problems/maximum-number-of-subsequences-after-one-inserting/


class Solution {
public:
    long long numOfSubsequences(string s) {
        int n = s.size();
        if( n < 2 )
            return 0LL;

        // goal maximum number of LCT subsequences
        // after at most one insertion

        // edge case:
        // if there is no L and no C and no T to begin with, answer is 0
        // if there are two out of the three letters missing, answer is 0
        //    so like no L,C or no L,T or no C,T; answer is 0
        // even if we have all three char, if we don't have at least 2 in the
        //    right order, ans is 0

        // key insights via observations
        // inserting a L is most beneficial at the begin,
        //    in which case we are gaining the number of subsequences
        //    that the existing left most C delivers
        // inserting a T is most beneficial at the end
        // inserting a C is most beneficial at the postion,
        //    where the product of L's to the left and T's to the right
        //    is maximized
        // out of those three options, the max is the answer
        // example to excercise that s = "LLLCLLTCTL"


        vector<long long> ts(n+1,0LL); // counting T's from right to left
        vector<long long> cs(n+1,0LL); // counting and aggregating C's followed by T's

        vector<long long> tsplust(n+1,0LL); tsplust[n] = 1LL;
        vector<long long> csplust(n+1,0LL);
        long long resultplust = 0LL;

        long long result = 0LL;
        long long last_l = 0LL; // what the left most L can deliver

        // right to left
        for(int i = n-1; i >= 0; --i) {

            // counting T's
            ts[i] = ts[i+1] + (long long)(s[i] == 'T');

            // if C how many T's are to our right?
            // plus carry from C's to our right
            cs[i] = cs[i+1] + (s[i] == 'C' ? ts[i] : 0LL);

            if( s[i] == 'L' ) {
                // the current L can devliver cs[i]
                result += cs[i];
                last_l  = cs[i];
            }

            // added T
            tsplust[i] = tsplust[i+1] + (long long)(s[i] == 'T');
            csplust[i] = csplust[i+1] + (s[i] == 'C' ? tsplust[i] : 0LL);
            if( s[i] == 'L' ) {
                resultplust += csplust[i];
            }

        }

        // cout << "result w/o adding a char " << result << endl;
        long long a = result + cs[0];   // adding L to the left

        long long b = resultplust;      // adding T to the right

        // solve for C somwhere with Ls2left and Ts2right

        // assume we would insert C to the right of i
        // hence investigating 0 <= i < n-1
        vector<int> Ls2left(n,0);
        if( s[0] == 'L' )
            Ls2left[0] = 1;
        for(int i = 1; i < n-1; ++i)
            Ls2left[i] = Ls2left[i-1] + (s[i] == 'L');

        vector<int> Ts2right(n,0);
        for(int i = n-2; i >= 0; --i)
            Ts2right[i] = Ts2right[i+1] + (s[i+1] == 'T');

        long long addend = 0LL;
        for(int i = n-1; i >= 0; --i) {
            long long p = (long long)Ls2left[i] * (long long)Ts2right[i];
            addend = max(addend, p);
        }
        long long c = result + addend;

        return max({a,b,c});
    }
};
