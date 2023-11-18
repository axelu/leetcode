
// 2227. Encrypt and Decrypt Strings
// https://leetcode.com/problems/encrypt-and-decrypt-strings/





/*
        for(string& s: *_values)
            cout << s << " ";
        cout << endl;

        for(int i = 0; i < 4; ++i)
            cout << _values->at(i) << " ";
        cout << endl;
 */
class Encrypter {
private:
    vector<char>* _keys;
    vector<string>* _values;
    // vector<string>* _dictionary;
    int char2key[26];
    unordered_map<string,vector<int>> value2keys;

    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    Trie* root;

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

    // DFS
    int search(vector<vector<char>>& word2, int pos, Trie* tn) {
        int word2_sz = word2.size();
        if( pos == word2_sz )
            return tn->endOfWord;

        int ret = 0;
        for(int i = 0; i < word2[pos].size(); ++i) {
            int idx = word2[pos][i] - 'a';
            if( tn->children[idx] != nullptr )
                ret += search(word2,pos+1,tn->children[idx]);
        }

        return ret;
    }


public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        _keys = &keys;
        _values = &values;
        // _dictionary = &dictionary;

        memset(char2key,-1,sizeof char2key);
        for(int i = 0; i < keys.size(); ++i)
            char2key[keys[i]-'a'] = i;

        for(int i = 0; i < values.size(); ++i)
            value2keys[values[i]].push_back(i);


        root = init();
        for(string& s : dictionary)
            add(s,root);
    }

    string encrypt(string word1) {
        string ret = "";
        for(char c: word1) {
            int i = char2key[c-'a'];
            if( i == -1 )
                return "";
            ret += _values->at(i); // assume i < _values.size()
        }
        return ret;
    }

    int decrypt(string word2) {
        int w2_sz = word2.size();
        vector<vector<char>> v2(w2_sz/2);         // is guaranteed that word2.length is even
        for(int k = 0; k < w2_sz; k += 2) {
            auto f = value2keys.find(word2.substr(k,2));
            if( f == value2keys.end() )
                return 0;
            for(int i: f->second)
                v2[k/2].push_back(_keys->at(i));
        }

        return search(v2,0,root);
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */
