
// 3777. Minimum Deletions to Make Alternating Substring
// https://leetcode.com/problems/minimum-deletions-to-make-alternating-substring/



class Solution {
private:
    pair<int,int> t[200000]; // segment tree memory efficient indexing, range query (sum), point update

    // debug
    void printTree(int n) {
        for(int i = 1; i < n; ++i)
            cout << "t[" << i << "]: " << t[i].first << " " << t[i].second << endl;
        return;
    }

    pair<int,int> combine(pair<int,int>& a, pair<int,int>& b) {
        if( a.first == -1 )
            return b;
        if( b.first == -1 )
            return a;
        // AA 0
        // AB 1
        // BA 2
        // BB 3
        // 0 0 -> AA AA = 1
        // 0 1 -> AA AB = 1
        // 0 2 -> AA BA = 0
        // 0 3 -> AA BB = 0
        // 1 0 -> AB AA = 0
        // 1 1 -> AB AB = 0
        // 1 2 -> AB BA = 1
        // 1 3 -> AB BB = 1
        // 2 0 -> BA AA = 1
        // 2 1 -> BA AB = 1
        // 2 2 -> BA BA = 0
        // 2 3 -> BA BB = 0
        // 3 0 -> BB AA = 0
        // 3 1 -> BB AB = 0
        // 3 2 -> BB BA = 1
        // 3 3 -> BB BB = 1
        int first = a.first + b.first + !((a.second & 1) ^ ((b.second & 2)>>1));
        int second = (a.second & 2) + (b.second & 1);
        return {first, second};
    }

    void build(string& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {0, a[tl] == 'A' ? 0 : 3};;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // range query (sum)
    pair<int,int> get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {-1, -1};
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

    // point update
    void update(int v, int tl, int tr, int pos) {
        // flip position, hence no new value needed
        if (tl == tr) {
            t[v].second = t[v].second == 3 ? 0 : 3;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();
        build(s, 1, 0, n-1);

        vector<int> ans;
        for(int i = 0; i < queries.size(); ++i) {
            if( queries[i][0] == 1 ) {
                update(1, 0, n-1, queries[i][1]);
            } else {
                ans.push_back(get(1, 0, n-1, queries[i][1], queries[i][2]).first);
            }
        }

        return ans;
    }
};
