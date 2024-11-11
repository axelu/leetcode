
// 3291. Minimum Number of Valid Strings to Form Target I
// https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/





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

    Trie* root;

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


public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();

        root = init();
        for(int i = 0; i < words.size(); ++i)
            add(words[i], root);

        int A[n+1];
        for(int i = 0; i <= n; ++i)
            A[i] = 5001;

        // array<int,2> // steps, pos
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        };

        priority_queue<array<int,2>, vector<array<int,2>>, decltype(cmp)> pq(cmp);
        pq.push({0,0});
        A[0] = 0;
        while( !pq.empty() ) {
            int steps = pq.top()[0];
            int pos = pq.top()[1];
            pq.pop();

            if( pos == n )
                return steps;

            struct Trie* tn = root;

            for(int i = pos; i < n; ++i) {
                int idx = target[i] - 'a';
                if (!tn->children[idx]) {
                    // we have no choice but to start from root again
                    // unless we have not made it anywhere
                    if( i != pos && steps + 1 < A[i] ) {
                        A[i] = steps + 1;
                        pq.push({steps + 1, i});
                    }
                    break;
                }

                // we have a choice
                //    start to search from root again OR
                //    keep going OR

                if( steps + 1 < A[i+1] ) {
                    A[i+1] = steps + 1;
                    pq.push({steps + 1, i+1});
                }

                tn = tn->children[idx];
            }
        }

        return -1;
    }
};
