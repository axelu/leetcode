
// 1542. Find Longest Awesome Substring
// https://leetcode.com/problems/find-longest-awesome-substring/




class Solution {
public:
    int longestAwesome(string& s) {
        int n = s.size();

        // s[i] is only digits
        // let us track a bit mask of length 10 (digits 0-9) where the kth bit is 0 if even occurence of digit
        // or the kth bit is 1 if odd occurence of digit
        // example
        //           0123456789012
        // bitmask   1234545678867
        // bit   9   0000000000000
        // bit   8   0000000001000
        // bit   7   0000000011110
        // bit   6   0000000111100
        // bit   5   0000110000000
        // bit   4   0001100000000
        // bit   3   0011111111111
        // bit   2   0111111111111
        // bit   1   1111111111111
        // bit   0   0000000000000
        //
        // observation
        // take position 6 as an example 1234545, which palindrome
        //   bitmask (most significant bit left) 0000001110
        //   we saw the same bitmask last at pos 2, which means we have an even number of any digit in range [3,6] inclusive
        // additionally, if we take the current bitmask and check for the latest occurance
        // where we are off by 1 bit, we will know if we can extend the substring

        // bitmask of 0-9 -> 1111111111 -> 1023 decimal

        unordered_map<int,int> um;
        um[0] = -1; // initially all digits are there 0 (even) times and index '-1'

        int ans = 1;

        int mask = 0;
        for(int i = 0; i < n; ++i) {
            mask ^= (1<<(s[i]-'0'));
            auto p = um.insert({mask,i});
            if( !p.second ) {
                ans = max(ans, i - p.first->second);
            }

            for(int k = 0; k < 10; ++k) {
                int t = mask ^ (1<<k);
                auto f = um.find(t);
                if( f != um.end() )
                    ans = max(ans, i - f->second);
            }
        }

        return ans;
    }
};
