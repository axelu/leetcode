

// 1897. Redistribute Characters to Make All Strings Equal
// https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/


class Solution {
public:
    bool makeEqual(vector<string>& words) {
        // only the frequency of characters matters
        // answer is true if all characters can be divided equally among all strings

        int cnt[26];memset(cnt,0,sizeof cnt);
        int n = words.size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < words[i].size(); ++j)
                ++cnt[words[i][j]-'a'];

        for(int i = 0; i < 26; ++i)
            if( cnt[i] % n != 0 )
                return false;

        return true;
    }
};
