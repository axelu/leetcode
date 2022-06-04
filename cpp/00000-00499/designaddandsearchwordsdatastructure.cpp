
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

    void add(string& s, Trie* tn) {
        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    bool find(string& s, int i, Trie* tn) {

        char ch;
        int idx;
        for (; i < s.length(); ++i) {
            if( s[i] == '.' ) {
                for(idx = 0; idx < 26; ++idx)
                    if( tn->children[idx] && find(s,i+1,tn->children[idx]) )
                        return true;
                
                return false;
            } else {
                idx = s[i] - 'a';
                if( !tn->children[idx] )
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
        add(word,dic);
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
