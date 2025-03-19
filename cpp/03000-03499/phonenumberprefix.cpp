
// 3491. Phone Number Prefix
// https://leetcode.com/problems/phone-number-prefix/




class Solution {
private:
    struct Trie {
        struct Trie* children[10];
        bool endOfWord;
    };

    Trie* dic;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 10; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    bool add(string& s, Trie* tn) {
        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] - '0';
            if (!tn->children[idx]) {
                tn->children[idx] = init();
            } else {
                if( tn->children[idx]->endOfWord )
                    return false;
            }

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;

        return true;
    }

public:
    bool phonePrefix(vector<string>& numbers) {

        sort(begin(numbers),end(numbers),[](const string& a, const string& b){
            if( a.size() < b.size() ) {
                return true;
            } else if( a.size() == b.size() ) {
                return a < b;
            }
            return false;
        });

        dic = init();

        add(numbers[0], dic);
        for(int i = 1; i < numbers.size(); ++i)
            if( !add(numbers[i], dic) )
                return false;

        return true;
    }
};
