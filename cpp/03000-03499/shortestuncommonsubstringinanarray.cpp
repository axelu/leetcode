
// 3076. Shortest Uncommon Substring in an Array
// https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/




/* each word in arr has n * (n+1)/2 substrings
 * worst case: 100 words and each word has a length of 20 char
 * -> 100 * (20 * (20+1)/2) = 100 * 210 = 21000
 * idea
 *     construct a Trie containing each substring of every word
 *     keep track also of each substring for each word
 *     sort the substrings for each word lexicographically and
 *     determine the number of occurences in the Trie
 *     the first substring with occurence == 1 is the ans[i]
 *     if no substring with occurence == 1 then ans[i] is an empty string
 */
class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = 0;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* dic;

    // lexicographical sort with a twist -> shortest first
    struct StringCmp {
        bool operator()(const string& a, const string& b) const {
            int a_sz = a.size();
            int b_sz = b.size();
            if( a_sz < b_sz ) {
                return true;
            } else if( a_sz == b_sz ) {
                for(int i = 0; i < a_sz; ++i)
                    if( a[i] != b[i] )
                        return a[i] < b[i];
            }
            return false;
        }
    };

    void add(string& s, set<string, StringCmp>& substrs) {
        struct Trie* tn = dic;
        string ss = "";

        for(int i = 0; i < s.size(); ++i) {
            char c = s[i];
            ss = ss + c;
            // cout << "    " << ss << endl;
            auto p = substrs.insert(ss);
            int idx = c - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
            if( p.second )
                tn->endOfWord += 1;
        }

        // last node is end of word
        // tn->endOfWord += 1;
    }

    bool search(string& s) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            // it is guaranteed the s exists in Trie
            // if (!tn->children[idx])
            //    return false;

            tn = tn->children[idx];
        }

        return tn->endOfWord == 1;
    }


public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();

        dic = init();
        set<string, StringCmp> substrings[n];
        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << " " << arr[i] << endl;
            int l = arr[i].size();
            set<string, StringCmp> substrs;
            for(int j = 0; j < l; ++j) {
                string ss = arr[i].substr(j, l-j);
                // cout << "  " << ss << endl;
                add(ss, substrs);
            }
            substrings[i] = substrs;
        }

        vector<string> ans(n);

        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << " " << arr[i] << endl;
            // for(string ss: substrings[i])
            //    cout << "  " << ss << " ";

            for(string ss: substrings[i]) {
                // cout << "  " << ss << " ";
                if( search(ss) ) {
                    ans[i] = ss;
                    break;
                }
            }
            // cout << endl;
        }

        return ans;
    }
};
