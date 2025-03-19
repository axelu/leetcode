
// 3485. Longest Common Prefix of K Strings After Removal
// https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/





class Solution {
private:
    multiset<int> by_length[10001];

    int k;

    int t; // quick check

    struct Trie {
        struct Trie* children[26];
        int cnt;
    };

    Trie* dic;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cnt = 0;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* tn) {
        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] - 'a';
            if (!tn->children[idx]) {
                tn->children[idx] = init();
                tn = tn->children[idx];
                tn->cnt = 1;
                by_length[i+1].insert(1);

            } else {
                tn = tn->children[idx];
                if( tn->cnt > 0 ) {
                    auto it = by_length[i+1].find(tn->cnt);
                    by_length[i+1].erase(it);
                }
                ++tn->cnt;
                by_length[i+1].insert(tn->cnt);

                // for quick check
                if( tn->cnt >= k ) {
                    t = max(t, i+1);
                }

                // TODO remember best and second best
                // idea is to use that when we remove
                // if we remove best, then second best
                // otherwise it is best

            }
        }

        return;
    }

    void del(string& s, Trie* tn) {
        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] - 'a';
            tn = tn->children[idx];

            auto it = by_length[i+1].find(tn->cnt);
            by_length[i+1].erase(it);
            --tn->cnt;
            if( tn->cnt > 0 )
                by_length[i+1].insert(tn->cnt);
        }

        return;
    }


public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        // 1 <= k <= words.length <= 1e5
        // 1 <= words[i].length <= 1e4

        int n = words.size();

        vector<int> ans(n,0);

        // edge case k == n
        // answer is 0 for all indices
        if( k == n )
            return ans;

        // edge case k == 1
        // answer is length of longest word unless
        // it is removed, then answer is length of second longest word
        if( k == 1 ) {
            int maxmaxl = 0;
            int maxl    = 0;
            for(string& s: words) {
                int l = s.size();
                if( l >= maxmaxl ) {
                    maxl = maxmaxl;
                    maxmaxl = l;
                } else if( l > maxl ) {
                    maxl = l;
                }
            }
            for(int i = 0; i < n; ++i) {
                int l = words[i].size();
                ans[i] = l == maxmaxl ? maxl : maxmaxl;
            }
            return ans;
        }

        this->k = k;

        dic = init();

        t = 0;
        int mxlen = 0;
        for(string& s: words) {
            add(s, dic);
            mxlen = max(mxlen, (int)s.size());
        }
        // if we didn't see any crossing of k
        // then we are done
        if( t == 0 )
            return ans;


        // TODO
        // if we either have at least one occurence of
        // our best answer and its count it k+1, then
        // removing no word will change that
        // if we have at two or more occurences of
        // our best answer with a count of k, then also
        // removing no word will change that


        for(int i = 0; i < n; ++i) {
            // if we are at a word whos lenght is less than best answer
            // then removing that word has no impact
            if( words[i].size() < t ) {
                ans[i] = t;
                continue;
            }

            del(words[i], dic);

            int res = 0;
            for(int j = mxlen; j >= 0; --j)
                if( !by_length[j].empty() && *by_length[j].rbegin() >= k ) {
                    res = j;
                    break;
                }

            ans[i] = res;

            add(words[i], dic);
        }

        return ans;
    }
};
