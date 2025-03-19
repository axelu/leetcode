
// 3435. Frequencies of Shortest Supersequences
// https://leetcode.com/problems/frequencies-of-shortest-supersequences/






class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    // dfs to determine if graph has cycle
    // mask tells us if a given node is there twice, which will allow to break cycle
    bool has_cycle(unordered_map<int,vector<int>>& g, int u, vector<bool>& seen, int& mask) {
        if( mask & (1<<u) )
            return false;
        if( seen[u] )
            return true;

        seen[u] = true;

        for(int v : g[u]) {
            if( has_cycle(g, v, seen, mask) )
                return true;
        }

        // if we are here, we know starting from u we don't have a cycle
        // we may come back to u from another incoming edge and need to signal
        // that from u on out, no cycle exists, we can do that via our mask
        mask |= (1<<u);

        return false;
    }

public:
    vector<vector<int>> supersequences(vector<string>& words) {
        int n = words.size(); // 1 <= words.length <= 256; words[i].length == 2
        // All strings in words will altogether be composed of no more than 16 unique lowercase letters.
        // All strings in words are unique.

        // A shortest common supersequence (SCS) is a string of minimum length
        // that contains each string in words as a subsequence

        // with 16 objects (chars) and sample size 16 -> 20922789888000 permutations
        // however, the 'words' give us ordering of the chars -> directed graph

        // map chars to indices
        unordered_map<char,int> chrmap;
        // create directed graph from words, the words are our directed edges
        unordered_map<int,vector<int>> g;
        int chrcnt = 0;
        for(auto& word: words) {
            int chridx0;
            auto p0 = chrmap.insert({word[0],chrcnt});
            if( p0.second )
                chridx0 = chrcnt++;
            else
                chridx0 = p0.first->second;

            int chridx1;
            auto p1 = chrmap.insert({word[1],chrcnt});
            if( p1.second )
                chridx1 = chrcnt++;
            else
                chridx1 = p1.first->second;

            g[chridx0].push_back(chridx1);
        }
        //for(auto p: chrmap)
        //    cout << p.first << ":" << p.second << " ";
        //cout << endl;

        // a shortest common supersequence (SCS) needs to at minimum include each unique character
        // at least once
        // treating words as edges in a graph, if our graph does NOT have a cycle, then using
        // each character once is our shortest (and with that only) SCS
        // if the graph has one or more cycles, we need to find the minimum number of nodes aka
        // vertices aka chars to add, to break the cycle
        // example ["ab","ba"] -> edges a->b and b->a
        // a graph with one a and one b has a cycle    a->b
        //                                             ^__|
        // but if we add an a: a->b->a  or b: b->a->b
        // we break the cycle

        vector<vector<int>> ans;
        //vector<bool> seen(chrcnt, false);
        //cout << has_cycle(g,0,seen,4) << endl;
        //return ans;


        // as said before, each char is at least ones in our answer,
        // but 1 or more are there 2 times
        // we will test each possibility, and keep only the shortest ones
        // so lets say 2a's and 2b's would be valid (total 4 char),
        // but also 1a and 2b's OR 2a's and 1b (total 3 char)
        // we would only return the two solutions with 3 char,
        // because it is shorter than 4 char
        // we just use bits to determine where we allow 2 chars
        // at most 16 uniqe char -> 2^16 - 1 = 65536 - 1 = 65535
        int mn_len = chrcnt;
        for( int i = 0; i <= pow(2,chrcnt)-1; ++i) {
            int _setbits = countSetBits(i);
            if( _setbits > mn_len ) // shorter answer already exists
                continue;

            vector<bool> seen(chrcnt, false);
            bool is_valid = true;
            int mask = i;
            for(int u = 0; u < chrcnt && is_valid; ++u)
                if( !seen[u] )
                    is_valid = !has_cycle(g,u,seen,mask);

            if( is_valid && _setbits < mn_len) {
                ans.clear();
                mn_len = _setbits;
            }
            if( is_valid ) {
                vector<int> t(26,0);
                for(auto& p: chrmap)
                    t[p.first-'a'] = i & (1<<p.second) ? 2 : 1;
                ans.push_back(t);
            }
        }

        return ans;
    }
};



/* test examples


["ab","ba"]
["aa","ac"]
["aa","bb","cc"]
["ab","cz"]
["db","ab","ac","ca"]
["pr","rq","qp"]




*/
