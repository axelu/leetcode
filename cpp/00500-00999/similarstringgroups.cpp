
// 839. Similar String Groups
// https://leetcode.com/problems/similar-string-groups/



class Solution {
private:
    int * parent;

    // disjoint-set union-find
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

    bool is_similar(vector<string>& strs, int a, int b) {
        // strs[a] and strs[b] are anagrams
        int n = strs[a].size();
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if( strs[a][i] != strs[b][i] ) {
                ++cnt;
                if( cnt > 2 )
                    return false;
            }

        return true;
    }

public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();

        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( is_similar(strs,i,j) )
                    unite(i,j);

        unordered_set<int> us;
        for(int i = 0; i < n; ++i)
            us.insert(findRoot(i));

        return us.size();
    }
};
