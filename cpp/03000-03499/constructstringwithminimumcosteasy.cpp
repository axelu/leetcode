
// 3253. Construct String with Minimum Cost (Easy)
// https://leetcode.com/problems/construct-string-with-minimum-cost-easy/


class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        long cost;
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cost = 200000001L;
        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }
    
    Trie* root;

    void add(string& s, long cost, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        tn->cost = min(tn->cost, cost);
        // last node is end of word
        tn->endOfWord = true;
    }
    
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        
        root = init();
        int words_sz = words.size(); // words.length == costs.length        
        for(int i = 0; i < words_sz; ++i)
            add(words[i], costs[i], root);

        int n = target.size();
        
        // basically Dijkstra
        // BFS
        // pair<int,long> -> index in target, cost so far
        auto cmp = [](pair<int,long>& a, pair<int,long>& b) {
            if( a.second > b.second ) {
                return true;
            } else if( a.second == b.second ) {
                if( a.first < b.first ) {
                    return true;
                }
            }
            return false;
        };

        priority_queue<pair<int,long>,vector<pair<int,long>>,decltype(cmp)> pq(cmp);
        pq.push({0,0});
        
        vector<long> A(n, 200000001L);
        
        while( !pq.empty() ) {
            int i = pq.top().first; // really next i
            long cost_so_far = pq.top().second;
            pq.pop();

            struct Trie* tn = root;

            for(; i < n; ++i) {
                int idx = target[i] - 'a';
                if (!tn->children[idx])
                    break;

                tn = tn->children[idx];
                if( tn->endOfWord ) {
                    // we have a choice
                    //    keep going OR
                    //    take the current word (take its cost) and look for a new word to continue

                    // special case
                    if( i == n-1 ) {
                        A[n-1] = min(A[n-1], cost_so_far + tn->cost);
                        break;
                    }
                    
                    // keep going

                    // look for new word
                    long b = cost_so_far + tn->cost;
                    if( b < A[i] ) {
                        A[i] = b;
                        pq.push({i+1, b});
                    }
                }
            }
            
        }
        
        return A[n-1] < 200000001 ? A[n-1] : -1;
    }
};



// 718 / 749 test cases passed, then TLE as of 8/20/2024
// possible idea: assign each tn a unique id 0, 1, ...
// based on constraints max 100000
// then DP on search based on i and tn id

// DFS

class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        long cost;
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cost = 200000001L;
        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* root;

    void add(string& s, long cost, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        tn->cost = min(tn->cost, cost);
        // last node is end of word
        tn->endOfWord = true;
    }

    // recursive search, dfs
    long search(string& s, int n, int i, Trie* dic) {
        // if( i == n )
        //     return 0L;

        struct Trie* tn = dic;

        long ret = 200000001;

        for(; i < n; ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return ret;

            tn = tn->children[idx];
            if( tn->endOfWord ) {
                // we have a choice
                //    keep going OR
                //    take the current word (take its cost) and look for a new word to continue

                // special case
                if( i == n-1 )
                    return tn->cost;

                // keep going
                long a = search(s, n, i+1, tn);

                // look for new word
                long b = tn->cost + search(s, n, i+1, root);

                return min(a, b);
            }
        }

        return ret;
    }

public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {

        root = init();
        int words_sz = words.size(); // words.length == costs.length
        for(int i = 0; i < words_sz; ++i)
            add(words[i], costs[i], root);

        long ans = search(target, target.size(), 0, root);
        // cout << ans << endl;

        return ans < 200000001 ? ans : -1;
    }
};



// BFS fails with Memory Limit exceeded on same test case as DFS

class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        long cost;
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cost = 200000001L;
        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    Trie* root;

    void add(string& s, long cost, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        tn->cost = min(tn->cost, cost);
        // last node is end of word
        tn->endOfWord = true;
    }

    // recursive search, dfs
    long search(string& s, int n, int i, Trie* dic) {
        // if( i == n )
        //     return 0L;

        struct Trie* tn = dic;

        long ret = 200000001;

        for(; i < n; ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return ret;

            tn = tn->children[idx];
            if( tn->endOfWord ) {
                // we have a choice
                //    keep going OR
                //    take the current word (take its cost) and look for a new word to continue

                // special case
                if( i == n-1 )
                    return tn->cost;

                // keep going
                long a = search(s, n, i+1, tn);

                // look for new word
                long b = tn->cost + search(s, n, i+1, root);

                return min(a, b);
            }
        }

        return ret;
    }

public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {

        root = init();
        int words_sz = words.size(); // words.length == costs.length
        for(int i = 0; i < words_sz; ++i)
            add(words[i], costs[i], root);

        int n = target.size();
        // long ans = search(target, n, 0, root);
        // cout << ans << endl;

        // return ans < 200000001 ? ans : -1;


        // BFS
        // pair<int,long> -> index in target, cost so far
        auto cmp = [](pair<int,long>& a, pair<int,long>& b) {
            if( a.second > b.second ) {
                return true;
            } else if( a.second == b.second ) {
                if( a.first < b.first ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<pair<int,long>,vector<pair<int,long>>,decltype(cmp)> pq(cmp);
        pq.push({0,0});

        long ans = 200000001;

        while( !pq.empty() ) {
            int i = pq.top().first; // really next i
            long cost_so_far = pq.top().second;
            pq.pop();

            /*
            if( i == n ) {
                ans = min(ans, cost_so_far);
                continue;
            }
            */

            struct Trie* tn = root;

            for(; i < n; ++i) {
                int idx = target[i] - 'a';
                if (!tn->children[idx])
                    break;

                tn = tn->children[idx];
                if( tn->endOfWord ) {
                    // we have a choice
                    //    keep going OR
                    //    take the current word (take its cost) and look for a new word to continue

                    // special case
                    if( i == n-1 ) {
                        ans = min(ans, cost_so_far + tn->cost);
                        break;
                    }

                    // keep going

                    // look for new word
                    long b = cost_so_far + tn->cost;
                    if( b < ans )
                        pq.push({i+1, b});
                }
            }

        }

        // cout << ans << endl;
        return ans < 200000001 ? ans : -1;;
    }
};
