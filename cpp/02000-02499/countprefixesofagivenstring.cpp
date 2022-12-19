
// 2255. Count Prefixes of a Given String
// https://leetcode.com/problems/count-prefixes-of-a-given-string/




class Solution {
public:
    int countPrefixes(vector<string>& words, string s) {
        int n = s.size();
        int cnt = 0;
        for(auto& word: words) {
            int k = word.size();
            if( k > n )
                continue;
            int i = 0;
            for(; i < k; ++i)
                if( word[i] != s[i] )
                    break;
            if( i == k )
                ++cnt;
        }

        return cnt;
    }
};
