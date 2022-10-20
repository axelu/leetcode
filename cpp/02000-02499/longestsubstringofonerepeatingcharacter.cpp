
// 2213. Longest Substring of One Repeating Character
// https://leetcode.com/problems/longest-substring-of-one-repeating-character/


class Solution {
private:
    struct T {
        int mx;          // length of the longest substring of that segment consisting of only 1 repeating char
        char left_char;  // leftmost char of the segment
        int suffix_lgt;  // max length of a suffix substring consisting of only 1 repeating character starting at leftmost char
        char right_char; // rightmost char of the segment
        int prefix_lgt;  // max length of a prefix substring consisting of only 1 repeating character starting at rightmost char
    };

    T t[400000]; // segment tree

    T merge(T& l, int ln, T& r, int rn) {
        T tn;
        tn.mx = max(l.mx,r.mx);
        tn.left_char  = l.left_char;
        tn.right_char = r.right_char;
        tn.suffix_lgt = l.suffix_lgt;
        tn.prefix_lgt = r.prefix_lgt;

        if( l.right_char == r.left_char ) {
            // 'new substring consisting of only one char' created
            // around the middle of the left and right segment
            int m = l.prefix_lgt + r.suffix_lgt;
            tn.mx = max(tn.mx,m);
            if( l.prefix_lgt == ln )
                tn.suffix_lgt += r.suffix_lgt;
            if( r.suffix_lgt == rn )
                tn.prefix_lgt += l.prefix_lgt;
        }
        return tn;
    }

    void build(string& s, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {1,s[tl],1,s[tl],1};
        } else {
            int tm = (tl + tr) / 2;
            build(s, v*2, tl, tm);
            build(s, v*2+1, tm+1, tr);
            t[v] = merge(t[v*2],tm-tl+1,t[v*2+1],tr-tm); // tr-(tm+1)+1 -> tr - tm
        }
    }

    void update(int v, int tl, int tr, int pos, char new_char) {
        if (tl == tr) {
            t[v].left_char = new_char;
            t[v].right_char = new_char;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, new_char);
            else
                update(v*2+1, tm+1, tr, pos, new_char);
            t[v] = merge(t[v*2],tm-tl+1,t[v*2+1],tr-tm); // tr-(tm+1)+1 -> tr - tm
        }
    }

public:
    vector<int> longestRepeating(string& s, string& queryCharacters, vector<int>& queryIndices) {
        // 1 <= s.length <= 10^5
        int n = s.size();
        build(s,1,0,n-1);

        int k = queryCharacters.size(); // queryCharacters.length == queryIndices.length
        vector<int> ans(k);
        for(int i = 0; i < k; ++i) {
            update(1,0,n-1,queryIndices[i],queryCharacters[i]);
            ans[i] = t[1].mx;
        }

        return ans;
    }
};
