
// 1048. Longest String Chain
// https://leetcode.com/problems/longest-string-chain/
// day 17 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3746/






class Solution {
private:
    unordered_map<string,int> mem;

    bool isPredecessor(string& a, string& b) {
        // 0 < a.size() = b.size()-1
        // returns if a is a predecessor of b
        // a is predecessor of b if and only if
        // we can add exactly one letter anywhere in a to make it equal to b
        // hence the opposite holds true, if we can remove a char from b
        // and it makes b equal to a, then a is a predecessor of b

        int na = a.size(),j;
        for(int i = 0; i < b.size(); ++i) { // index in b
            // skip char at index i
            j = 0;
            for(; j < na; ++j) {            // index in a
                if( j < i ) {
                    if( a[j] != b[j] )   break;
                } else {
                    if( a[j] != b[j+1] ) break;
                }
            }
            if( j == na ) return true;
        }
        return false;
    }

    int dfs(map<int,vector<string>>::reverse_iterator it,
            map<int,vector<string>>::reverse_iterator ite, string& word2) {

        auto f = mem.find(word2);
        if( f != mem.end() ) return f->second;

        int ret = 0;
        int l = 0;
        for(int i = 0; i < it->second.size(); ++i) {
            string word = it->second[i];
            if( isPredecessor(word,word2) ) {
                ret = 1;
                if( next(it) != ite )
                    l = max(l,dfs(next(it),ite,word));
            }
        }
        mem.insert({word2,ret+l});
        return ret + l;
    }

public:
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        if( n == 1 ) return 1;

        map<int,vector<string>> m;
        pair<map<int,vector<string>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = m.insert({words[i].size(),{words[i]}});
            if( !p.second )
                p.first->second.push_back(words[i]);
        }

        int l = 0;

        for(auto it = m.rbegin(); next(it) != m.rend(); ++it) {
            for(int i = 0; i < it->second.size(); ++i) {
                string word2 = it->second[i];
                if( mem.find(word2) != mem.end() ) continue;
                // check all words with length-1
                l = max(l,dfs(next(it),m.rend(),word2));
            }
        }

        return 1+l;
    }
};
