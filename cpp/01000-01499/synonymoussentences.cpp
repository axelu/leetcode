
// 1258. Synonymous Sentences
// https://leetcode.com/problems/synonymous-sentences/





class Solution {
private:
    int * parent;

    int findRoot(int i) {
		// chase parent of current element until it reaches root

        while(parent[i] != i) {
            // path compression
            // set each i to point to its grandparent
            // (thereby halving the path length), where i
            // is the node which comes in between path,
            // while computing root
            parent[i] = parent[parent[i]] ;
            i = parent[i];
        }
		return i;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}

    // map of unique words by string and by id
    unordered_map<string,int> by_str;
    unordered_map<int,string> by_id;
    int n; // nbr of unique words

    string path2text(vector<string>& path) {
        string s = "";
        for(int i = 0; i < path.size(); ++i) {
            if( i > 0 )
                s += ' ';
            s += path[i];
        }
        return s;
    }

    void dfs(vector<int>& txt, int i, vector<string>& path, vector<string>& ans) {
        int txt_sz = txt.size();
        if( i == txt_sz ) {
            ans.push_back(path2text(path));
            return;
        }

        // find the root of the current word
        int root = findRoot(txt[i]);
        // collect all synonyms
        vector<string> curr_synonyms;
        for(int k = 0; k < n; ++k)
            if( findRoot(k) == root )
                curr_synonyms.push_back(by_id[k]);
        // sort synonymns
        sort(curr_synonyms.begin(),curr_synonyms.end());
        for(string& s : curr_synonyms) {
            path.push_back(s);
            dfs(txt,i+1,path,ans);
            // backtrack
            path.pop_back();
        }
    }

public:
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        n = 0;
        // unique words in synonyms
        for(auto& v : synonyms) {
            if( !by_str.count(v[0]) ) {
                by_str[v[0]] = n;
                by_id[n] = v[0];
                ++n;
            }
            if( !by_str.count(v[1]) ) {
                by_str[v[1]] = n;
                by_id[n] = v[1];
                ++n;
            }
        }
        // unique words in text
        vector<int> txt;
        stringstream ss(text);
        string s;
        while( getline(ss,s,' ') ) {
            auto f = by_str.find(s);
            if( f == by_str.end() ) {
                by_str[s] = n;
                by_id[n] = s;
                txt.push_back(n);
                ++n;
            } else
                txt.push_back(f->second);
        }

        // union find
        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself
        for(auto& v : synonyms)
            unite(by_str[v[0]],by_str[v[1]]);

        vector<string> ans;
        vector<string> path;
        dfs(txt,0,path,ans);

        return ans;
    }
};
