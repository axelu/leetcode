
// 2573. Find the String with LCP
// https://leetcode.com/problems/find-the-string-with-lcp/






/* lcp (longest common prefix) between the substrings word[i,n-1] and word[j,n-1]
 * example 1
 * lcp matrix
 *           i
 *        0 1 2 3
 *        -------
 *    0 | 4 0 2 0
 * j  1 | 0 3 0 1
 *    2 | 2 0 2 0
 *    3 | 0 1 0 1
 *
 * the diagonal top left to bottom right should always be the same as shown
 * the matrix should be mirrorwed accross that top left to bottom right diagonal
 * row by row
 * i j lcp[i][j] word[i][n-1] word[j][n-1]
 * 0 0    4        abab           abab      lcp[i][j] should always be n
 * 0 1    0        abab            bab      if 0 tells us that char at pos 1 is different than pos 0
 * 0 2    2        abab             ab      tells us that starting at pos 2, 2 charaters from pos 0 repeat
 * 0 3    0        abab              b      ...
 * 1 0    0         bab           abab
 * 1 1    3         bab            bab
 * 1 2    0         bab             ab
 * 1 3    1         bab              b
 * 2 0    2          ab           abab
 * 2 1    0          ab            bab
 * 2 2    2          ab             ab
 * 2 3    0          ab              b
 * 3 0    0           b           abab
 * 3 1    1           b            bab
 * 3 2    0           b             ab
 * 3 3    1           b              b
 *
 * example 3 given in the problem points out, that we should not trust the matrix,
 *           meaning the matrix may not have integrity, in which case there is no answer
 */
class Solution {
private:
    bool is_valid(vector<vector<int>>& lcp, int n) {

        for(int i = 0; i < n; ++i) {
            if( lcp[i][i] != n - i )
                return false;

            for(int j = i+1; j < n; ++j)
                if( lcp[i][j] > n - j || lcp[i][j] != lcp[j][i] )
                    return false;
        }

        return true;
    }

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

public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size(); // n x n matrix
        if( !is_valid(lcp,n) )
            return "";

        // build a string based on lcp
        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself

        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ) {
                int k = lcp[i][j];
                if( k == 0 ) {
                    ++j;
                } else {
                    for(int s = i; s < i+k; ++s,++j) {
                        unite(s,j);
                    }
                }
            }
        }

        string s(n,'#');
        char nxt = 'a';
        for(int i = 0; i < n; ++i) {
            int root = findRoot(i);
            if( root == i ) {
                if( nxt > 'z' )
                    return "";
                s[i] = nxt++;
            } else {
                s[i] = s[root];
            }
        }

        // validate by building lcp matrix from s
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {

                int start1 = i;
                int start2 = j;
                int k = 0;
                while( s[start1] == s[start2] && k <= lcp[i][j] ) {
                    ++k;
                    ++start1;
                    ++start2;
                }
                if( k != lcp[i][j] )
                    return "";
            }
        }

        return s;
    }
};
