
// 126. Word Ladder II
// https://leetcode.com/problems/word-ladder-ii/



class Solution {
private:
    void dfs(unordered_map<string,vector<string>>& g,
             string& s,
             vector<string>& path,
             string& endWord,
             vector<vector<string>>& ans) {

        if( s == endWord ) {
            ans.push_back(path);
            reverse(ans.back().begin(),ans.back().end());
            return;
        }

        for(auto& t: g[s] ) {
            path.push_back(t);
            dfs(g,t,path,endWord,ans);
            // backtrack
            path.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;

        // init dictionary
        unordered_set<string> dic(wordList.begin(),wordList.end());

        // check if endWord is in wordList
        if( !dic.count(endWord) )
            return ans;


        int N = beginWord.size(); // endWord.length == beginWord.length == wordList[i].length
        if( 1 == N ) {
            vector<string> vs = {beginWord,endWord};
            ans.push_back(vs);
            return ans; // edge case
        }

        // lets build a directed graph from beginWord to endWord
        // that only has the shortest paths
        // because not all path will end at endWord, we will create
        // reverse edges and start our final process at endWord
        // BFS
        unordered_map<string,vector<string>> g;
        queue<string> q;
        q.push(beginWord);
        if( dic.count(beginWord) )
            dic.erase(beginWord);
        while( !q.empty() ) {
            if( q.front() == endWord )
                break;

            unordered_set<string> seen; // keep track of words added to queue
            queue<string> q_new;
            while( !q.empty() ) {
                string s = q.front();
                q.pop();

                // determine all neighbors of string s
                string t = s;
                for(int i = 0; i < N; ++i) {
                    char oldChar = t[i];
                    for(int k = 0; k < 26; ++k) {
                        char newChar = 'a'+k;
                        if( newChar == oldChar )
                            continue;
                        t[i] = newChar;
                        // is our new word in the dictionary?
                        if( dic.count(t) ) {
                            // create directed edge from t to s
                            g[t].push_back(s);
                            // have we added t already to the queue?
                            if( !seen.insert(t).second )
                                continue;
                            q_new.push(t);
                        }
                        // backtrack
                        t[i] = oldChar;
                    }
                }
            }
            // delete prior level words from dictionary
            for(auto& k: seen)
                dic.erase(k);
            q = q_new;
        }

        // populate ans
        vector<string> path{endWord}; // path ends at endWord
        dfs(g,endWord,path,beginWord,ans);
        return ans;
    }
};
