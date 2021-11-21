
// 211. Design Add and Search Words Data Structure
// https://leetcode.com/problems/design-add-and-search-words-data-structure/



class WordDictionary {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    Trie* dic;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s) {
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

    bool find(string& s, int idx, Trie* localDic) {
        struct Trie* tn = localDic;

        for (int i = idx; i < s.length(); i++) {
            if( s[i] == '.' ) {
                for(int c = 0; c < 26; ++c) {
                    char ch = 'a' + c;
                    s[i] = ch;
                    if( find(s,i,tn) ) return true;
                }
                s[i] = '.';
                return false;
            } else {
                int idx = s[i] - 'a';
                if (!tn->children[idx])
                    return false;

                tn = tn->children[idx];
            }
        }

        return( tn != NULL && tn->endOfWord );
    }
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        dic = init();
    }

    void addWord(string word) {
        add(word);
    }

    bool search(string word) {
        return find(word,0,dic);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
