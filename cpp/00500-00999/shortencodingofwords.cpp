
// 820. Short Encoding of Words
// https://leetcode.com/problems/short-encoding-of-words/
// day 6 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/588/week-1-march-1st-march-7th/3662/


class Solution {
private:
   struct Trie {
        Trie* children[26];
    };

    Trie* dic;

    Trie*  init() {
        Trie* tn =  new Trie;
        for(int i = 0; i < 26; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    void add(string& s) {
        struct Trie* tn = dic;
        for(int i = s.size()-1; i >= 0; --i) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] )
                tn->children[idx] = init();
            tn = tn->children[idx];
        }
    }

    void cnt(Trie* tn, int& ans, int depth) {
        bool hasChildren = false;
        for(int i = 0; i < 26; ++i)
            if( tn->children[i] ) {
                hasChildren = true;
                cnt(tn->children[i],ans,depth+1);
            }
        if( !hasChildren )
            ans += depth+1;
    }

public:
    int minimumLengthEncoding(vector<string>& words) {
        int n = words.size(); // 1 <= words.length <= 2000
        if( n == 1 ) return words[0].size()+1;

        dic = init();
        for(int i = 0; i < n; ++i)
            add(words[i]);

        int ans = 0;
        cnt(dic,ans,0);
        return ans;
    }
};
