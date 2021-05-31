
// 890. Find and Replace Pattern
// https://leetcode.com/problems/find-and-replace-pattern/




class Solution {
private:
    bool match(string& word, string& pattern) {
        unordered_map<char,char> um;
        unordered_map<char,char>::iterator f;
        int seen[26]; memset(seen,0,sizeof seen);
        for(int i = 0; i < word.size(); ++i) {
            f = um.find(pattern[i]);
            if( f == um.end() ) {
                if( seen[word[i]-'a'] ) return false;
                um.insert({pattern[i],word[i]});
                seen[word[i]-'a'] = 1;
            } else {
                if( f->second != word[i] ) return false;
            }
        }
        return true;
    }
public:
    vector<string> findAndReplacePattern(vector<string>& words, string& pattern) {
        vector<string> ans;
        for(int i = 0; i < words.size(); ++i)
            if( match(words[i],pattern) ) ans.push_back(words[i]);
        return ans;
    }
};
