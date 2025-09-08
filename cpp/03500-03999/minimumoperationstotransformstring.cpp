
// 3675. Minimum Operations to Transform String
// https://leetcode.com/problems/minimum-operations-to-transform-string/



class Solution {
public:
    int minOperations(string s) {
        int n = s.size(); // 1 <= n <- 5 * 1e5; s consists only of lowercase English letters.

        map<char,int> mp;
        for(char c: s)
            ++mp[c];

        auto it = mp.begin();
        if( it->first == 'a' )
            ++it;

        int ans = 0;
        for(; it != mp.end(); ++it) {
            char curr_char = it->first;
            char next_char = '{'; // char after z
            if( next(it) != mp.end() )
                next_char = next(it)->first;

            // we will advance the current char to the next char
            // distance from current char to the next char
            int dist = next_char - curr_char;

            ans += dist;
        }

        return ans;
    }
};
