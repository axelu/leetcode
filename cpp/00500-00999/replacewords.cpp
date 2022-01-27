
// 648. Replace Words
// https://leetcode.com/problems/replace-words/




class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    string search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return s;

            tn = tn->children[idx];
            if( tn->endOfWord ) return s.substr(0,i+1);
        }

        return s;
    }


public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie* root = init();
        for(string s : dictionary)
            add(s,root);

        stringstream ss(sentence);
        string ans,s;
        while( getline(ss,s,' ') )
            if( ans.empty() ) ans = search(s,root);
            else ans += " " + search(s,root);

        return ans;
    }
};
