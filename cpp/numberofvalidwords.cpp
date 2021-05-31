
// 1178. Number of Valid Words for Each Puzzle
// https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/




class Solution {
    void printIntBinary(unsigned int x) {
        for(int i = 25; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
    }

    struct Trie {
        struct Trie* children[2];
        int cnt;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cnt = 0;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        struct Trie* tn = dic;
        ++tn->cnt;

        for(int i = 25; i >= 0; --i) {
            if( s & (1 << i) ) {
                if (!tn->children[1])
                    tn->children[1] = init();
                tn = tn->children[1];
            } else {
                if (!tn->children[0])
                    tn->children[0] = init();
                tn = tn->children[0];
            }
            ++tn->cnt;
        }

    }

    int count(int mask, int f, int pos, Trie* dic) {
        struct Trie* tn = dic;
        int ret = 0;

        //  mask  continue
        //   bit
        //     0  subtree 0, add count from subtree 1
        //     1  subtree 1, dfs subtree 0 and add result

        int maskBit;
        for(int i = pos; i >= 0; --i) {
            maskBit  = mask  & (1 << i) ? 1 : 0;

            if( !maskBit ) {
                if( tn->children[1] ) {
                    // cout << "here" << endl;
                    ret += tn->children[1]->cnt;
                }
                if( !tn->children[0] )
                    break;
                tn = tn->children[0];
            } else {
                if( i != f ) {
                    if(tn->children[0] )
                        ret += count(mask,f,i-1,tn->children[0]);
                } else {
                    if( tn->children[0] )
                        ret += tn->children[0]->cnt;
                }
                if( !tn->children[1] )
                    break;
                tn = tn->children[1];
            }
        }
        return ret;
    }

    int string2mask(string& s) {
        int mask = 0;
        for(int i = 0; i < s.size(); ++i)
            mask |= (1 << (s[i]-'a'));
        return mask;
    }

    bool wordInPuzzle(int word, int puzzle) {
        int wordBit,puzzleBit;
        for(int i = 25; i >= 0; --i) {
            wordBit   = word   & (1 << i) ? 1 : 0;
            puzzleBit = puzzle & (1 << i) ? 1 : 0;
            if( wordBit && !puzzleBit )
                return false;
        }
        return true;
    }

public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        int n = words.size();
        int i,mask;

        Trie* root = init();
        for(i = 0; i < n; ++i) {
            mask = string2mask(words[i]);
            add(mask,root);
        }

        int t;
        vector<int> ans(puzzles.size());
        for(i = 0; i < puzzles.size(); ++i) {
            mask = string2mask(puzzles[i]);
            t = count(mask,puzzles[i][0]-'a',25,root);
            ans[i] = n-t;
        }
        return ans;
    }
};
