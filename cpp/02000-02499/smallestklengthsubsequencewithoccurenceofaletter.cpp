
// 2030. Smallest K-Length Subsequence With Occurrences of a Letter
// https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/






class Solution {
public:
    string smallestSubsequence(string& s, int k, char letter, int repetition) {
        int n = s.size();

        // count how many times letter occurs in s
        int letter_cnt_s = 0;
        for(char c: s)
            if( c == letter )
                ++letter_cnt_s;

        string ans = "";
        int letter_cnt_ans = 0; // initially we have 0 'letter' in ans

        for(int i = 0; i < n; ++i) {
            char c = s[i];
            int rem = n - i; // chars left in s including the current char

            // we want to use the current char if:
            //     c is less than the char in ans AND
            //     there are enough characters in current ans + remaining characters in s (ans.size == k in the end) AND
            //     there are enough letters in current ans + remaining letters in s (we need at least repetition letters in ans)

            while( ans.size() > 0
                   && c < ans.back()        // the current letter is better
                   && ans.size() + rem > k  // we can still make an answer of size k
                   && ( ans.back() != letter || letter_cnt_ans + letter_cnt_s > repetition ) ) { // we have enough letters

                // decrease count of letter in ans if we are removing letter
                if( ans.back() == letter )
                    --letter_cnt_ans;
                ans.pop_back();
            }

            if( ans.size() < k
                && ( c == letter || ans.size() - letter_cnt_ans < k - repetition) ) {

                ans.push_back(c);
                // increase count of letter in ans if current char is letter
                if( c == letter )
                    ++letter_cnt_ans;
            }

            // decrease count of letter in s if the current char is letter
            if( c == letter )
                --letter_cnt_s;
        }

        return ans;
    }
};
