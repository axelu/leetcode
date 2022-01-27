
// 880. Decoded String at Index
// https://leetcode.com/problems/decoded-string-at-index/
// day 20 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3572/



// from the solution
class Solution {
public:
    string decodeAtIndex(string S, int K) {
        long size = 0;
        int N = S.size();

        // Find size = length of decoded string
        for (int i = 0; i < N; ++i) {
            if (isdigit(S[i]))
                size *= S[i] - '0';
            else
                size++;
        }

        for (int i = N-1; i >=0; --i) {
            K %= size;
            if (K == 0 && isalpha(S[i]))
                return (string) "" + S[i];

            if (isdigit(S[i]))
                size /= S[i] - '0';
            else
                size--;
        }
        return "";
    }
};
