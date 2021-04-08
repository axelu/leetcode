
// 395. Longest Substring with At Least K Repeating Characters
// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
// day 26 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3544/


class Solution {
private:
    int longestSubstring(string &str, int s, int e, int k) {
        if( e < k ) return 0;

        int cnt[26] = {0};
        for(int i = s; i < e; ++i)
            ++cnt[str[i] - 'a'];

        for(int mid = s; mid < e; ++mid) {
            if( cnt[str[mid] - 'a'] >= k ) continue;
            int midNext = mid + 1;
            while(midNext < e && cnt[str[midNext] - 'a'] < k) midNext++;
            return max(longestSubstring(str, s, mid, k),longestSubstring(str, midNext, e, k));
        }
        return (e - s);
    }

public:
    int longestSubstring(string s, int k) {
        size_t n = s.size();
        return longestSubstring(s,0,n,k);
    }
};
