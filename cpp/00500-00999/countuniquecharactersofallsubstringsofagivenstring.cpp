
// 828. Count Unique Characters of All Substrings of a Given String
// https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/




class Solution {
public:
    int uniqueLetterString(string& s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        // we will travers s from left to right
        // if we add a letter that has not been see before
        //     then we can add length (current index + 1) to the prior index's score
        //     let us call that our normal score
        // however, we may encounter a char that has been seen before
        //     in that case we need to subtract from our normal score -2 times
        //     the number of times that we loose out, which is
        //     the index + 1 of when we saw the current char last
        //     let us call that index last_last_seen
        // but if the current letter has been seen more than once before,
        // in that case we are over compensating, so we must add those times
        // back in, let us call that index last_seen
        // with that we are getting the following formula for the score
        // at the current index i:
        //     let c be the index in ABC...XYZ
        //     dp[i] = dp[i-1] + (i+1) - (2*(lst_lst_seen[s[c]+1])) + (lst_seen[s[c]]+1)

        int dp[n];
        dp[0] = 1;

        int ans = 1;

        int lst_lst_seen[26];memset(lst_lst_seen,-1,sizeof lst_lst_seen);
        lst_lst_seen[s[0]-'A'] = 0;
        int lst_seen[26];memset(lst_seen,-1,sizeof lst_seen);

        for(int i = 1; i < n; ++i) {
            int c = s[i]-'A';
            dp[i] = dp[i-1] + (i+1) - (2*(lst_lst_seen[c]+1)) + (lst_seen[c]+1);
            ans += dp[i];

            lst_seen[c] = lst_lst_seen[c];
            lst_lst_seen[c] = i;
        }
        return ans;
    }
};
