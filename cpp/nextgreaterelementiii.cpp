
// 556. Next Greater element III
// https://leetcode.com/problems/next-greater-element-iii/
// day 23 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3578/

class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        size_t N = s.size();

        // quick check if there even is a digit we could swap
        int i = N - 1;
        for(; i > 0 && s[i] <= s[i - 1]; --i);
        if( !i ) return -1;

        int j = i, k = i;
        for(; k < N; ++k)
            if( s[k] > s[i - 1] && s[k] <= s[j] )
                j = k;

        swap(s[i - 1], s[j]);
        reverse(s.begin() + i, s.end());
        long long ans = stoll(s);
        return ans <= INT_MAX ? ans : -1;
    }
};
