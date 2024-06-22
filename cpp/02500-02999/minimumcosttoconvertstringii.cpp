
// 2977. Minimum Cost to Convert String II
// https://leetcode.com/problems/minimum-cost-to-convert-string-ii/




class Solution {
private:
    const long long INF = LLONG_MAX;

    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    Trie* root;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(const string& s, const int idx) {
        struct Trie* tn = root;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = idx;
    }

    long long mem[1000];

    long long rec(const string& source, const string& target, const int n, const int pos, long long **dist) {
        if( pos == n )
            return 0LL;

        if( mem[pos] != -1LL )
            return mem[pos];

        long long ret = LLONG_MAX;

        // try as long as equal
        // same substring -> 0 cost
        for(int i = pos; i < n; ++i) {
            if( source[i] != target[i] )
                break;
            ret = min(ret, rec(source,target,n,i+1,dist));
        }

        struct Trie* source_tn = root;
        struct Trie* target_tn = root;

        // search
        for(int i = pos; i < n; ++i) {
            int source_idx = source[i] - 'a';
            if( !source_tn->children[source_idx] )
                break;

            int target_idx = target[i] - 'a';
            if( !target_tn->children[target_idx] )
                break;

            source_tn = source_tn->children[source_idx];
            target_tn = target_tn->children[target_idx];

            int source_substring_idx = source_tn->endOfWord;
            if( source_substring_idx == -1 )
                continue;

            int target_substring_idx = target_tn->endOfWord;
            if( target_substring_idx == -1 )
                continue;

            if( dist[source_substring_idx][target_substring_idx] == INF )
                continue;

            long long t = rec(source,target,n,i+1,dist);
            if( t < INF )
                ret = min(ret, (long long)dist[source_substring_idx][target_substring_idx] + t);
        }

        return mem[pos] = ret;
    }

public:
    long long minimumCost(string& source, string& target, vector<string>& original, vector<string>& changed, vector<int>& cost) {

        // we need to figure out the cheapest cost to convert substring x to substring y.
        // once we know that, we can go from left to right through source and add up the cost.
        // at each position we need to see if a substring in source matches our originals and
        // if a substring in target of same length matches changed, then we will try that
        // there maybe a longer match at the same position, we will have to try that also (dynamic programming)
        // we will treat original and changed as a edges in a directed weighted graph

        // Floyd-Warshall
        unordered_map<string,int> substrings;
        int substring_idx = 0;
        for(string& s: original) {
            if( substrings.insert({s,substring_idx}).second )
                ++substring_idx;
        }
        for(string& s: changed) {
            if( substrings.insert({s,substring_idx}).second )
                ++substring_idx;
        }
        /*
        // debug
        for(auto& p: substrings)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        long long **dist;
        dist = new long long *[substrings.size()];
        for(int i = 0; i < substrings.size(); ++i) {
            dist[i] = new long long[substrings.size()];
            for(int j = 0; j < substrings.size(); ++j)
                dist[i][j] = i == j ? 0LL : INF;
        }

        // add edges
        for(int i = 0; i < cost.size(); ++i) {
            int u = substrings[original[i]];
            int v = substrings[changed[i]];
            long long w = cost[i];
            // only use if smaller
            dist[u][v] = min(dist[u][v], w);
        }

        for(auto itk = substrings.begin(); itk != substrings.end(); ++itk) {
            int k = itk->second;
            for(auto iti = substrings.begin(); iti != substrings.end(); ++iti) {
                int i = iti->second;
                for(auto itj = substrings.begin(); itj != substrings.end(); ++itj) {
                    int j = itj->second;
                    if( dist[i][k] <= INF - dist[k][j] && dist[i][j] > dist[i][k] + dist[k][j] ) // guarding against integer overflow
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // build a Trie for all substrings
        // use their index as endOfWord indicator
        root = init();
        for(auto& p: substrings)
            add(p.first,p.second);

        memset(mem,-1,sizeof mem);
        long long ans = rec(source,target,source.size(),0,dist);

        return ans == INF ? -1 : ans;
    }
};
