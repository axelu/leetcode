
// 1061. Lexicographically Smallest Equivalent String
// https://leetcode.com/problems/lexicographically-smallest-equivalent-string/



class Solution {
private:
    int parent[26];

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

    int findMinRoot(int i) {
        int p = findRoot(i);
        int k = 0;
        for(; k < 26; ++k)
            if( findRoot(k) == p ) break;
        return k;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}

public:
    string smallestEquivalentString(string A, string B, string S) {
        int i;
        for(i = 0; i < 26; ++i)
            parent[i] = i; // initially each node is connected to itself only

        int n = A.size(); // 1 <= A.size() == B.size() <= 1000;
        for(i = 0; i < n; ++i)
            unite(A[i]-'a',B[i]-'a');

        for(i = 0; i < S.size(); ++i)
            S[i] = findMinRoot(S[i]-'a')+'a';

        return S;
    }
};
