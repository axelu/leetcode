
// 1166. Design File System
// https://leetcode.com/problems/design-file-system/



class FileSystem {
private:
    struct Trie {
        struct Trie* children[27]; // abcdefghijklmnopqrstuvwxyz/
        int endOfWord;             // end of path
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;
        tn->endOfWord = -1;
        for (int i = 0; i < 27; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    Trie* root;

    Trie* search(string& s, Trie* dic) {
        struct Trie* tn = dic;
        int idx;
        for(int i = 0; i < s.length(); i++) {
            if( s[i] == '/' )
                idx = 26;
            else
                idx = s[i] - 'a';

            if( !tn->children[idx] )
                return nullptr;
            tn = tn->children[idx];
        }
        return tn != NULL ? tn : nullptr;
    }

    bool add(string& s, Trie* dic, int value) {
        struct Trie* tn = dic;
        int idx;
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == '/' )
                idx = 26;
            else
                idx = s[i] - 'a';

            if (!tn->children[idx])
                tn->children[idx] = init();
            tn = tn->children[idx];
        }

        if( tn->endOfWord != -1 )
            return false;

        tn->endOfWord = value;
        return true;
    }


public:
    FileSystem() {
       root = init();
    }

    bool createPath(string path, int value) {
        // parent path
        auto n = path.size();        // 2 <= path.length <= 100
        auto f = path.rfind('/');
        if( f == string::npos || f == n-1 || f == 1 )
            return -1;

        if( f == 0 ) // path directly from root, meaning no parent
            return add(path,root,value);

        string parentPath = path.substr(0,f); // without the /
        Trie* parent = search(parentPath,root);
        if( parent == nullptr || parent->endOfWord == -1 )
            return false;

        string childPath = path.substr(f);
        return add(childPath,parent,value);
    }

    int get(string path) {
        Trie* tn = search(path,root);
        return tn != nullptr ? tn->endOfWord : -1;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
