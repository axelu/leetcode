
// 720. Longest Word in Dictionary
// https://leetcode.com/problems/longest-word-in-dictionary/



class Solution {
public:
    string longestWord(vector<string>& words) {
        int n = words.size();
        string ans = "";
        if( n == 1 ) return words[0].size() == 1 ? words[0] : ans;

        unordered_set<string> s;
        for(int i = 0; i < n; ++i)
            s.insert(words[i]);

        sort(words.begin(),words.end(),[](const string& a, const string& b){
            return a.size() > b.size();
        });

        int l,j;
        string word,prefix;
        for(int i = 0; i < n; ++i) {
            word = words[i];
            l = word.size();
            if( l < ans.size() ) break; // we already found a word that is longer
            j = l-1;
            for(; l > 0; --l) {
                prefix = word.substr(0,l);
                if( s.find(prefix) == s.end() ) break;
            }
            if( l == 0 ) {
                if( ans.empty() ) {
                    ans = word;
                } else {
                    if( word < ans ) {
                        ans = word;
                    }
                }
            }
        }
        return ans;
    }
};
