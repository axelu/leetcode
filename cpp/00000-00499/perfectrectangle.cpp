
// 391. Perfect Rectangle
// https://leetcode.com/problems/perfect-rectangle/




class Solution {
private:
    // segment tree holding min and max, range query range update lazy propagation
    pair<int,int> t[160001]; // max 20000 rectangles, each will have 2 distinct y coordinates -> 40000, times 4 for segment tree
    bool marked[160001];

    /*
    void build(int x, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {x,x};
        } else {
            int tm = (tl + tr) / 2;
            build(x, v*2, tl, tm);
            build(x, v*2+1, tm+1, tr);
            t[v] = {x,x}; // simplified for initialization
        }
    }
    */

    pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        int mn = min(a.first,b.first);
        int mx = max(a.second,b.second);
        return make_pair(mn,mx);
    }

    void push(int v) {
        if (marked[v]) {
            t[v*2] = t[v*2+1] = t[v];
            marked[v*2] = marked[v*2+1] = true;
            marked[v] = false;
        }
    }

    // range query
    pair<int, int> get_min_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return make_pair(INT_MAX, INT_MIN);

        if (l == tl && r == tr)
            return t[v];

        push(v);

        int tm = (tl + tr) / 2;
        return combine(get_min_max(v*2, tl, tm, l, min(r, tm)),
                       get_min_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] = make_pair(new_val,new_val);
            marked[v] = true;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), new_val);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
            t[v] = combine(t[v*2],t[v*2+1]);
        }
    }

public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int n = rectangles.size(); // 1 <= rectangles.length <= 20000
        // rectangles[i].length == 4 -> rectangles[i] = [xi, yi, ai, bi]
        // bottom-left (xi, yi) and top-right point (ai, bi)

        // assumption
        //     xi < ai && ai - xi >= 1 && yi < bi && bi - yi >= 1

        // idea
        //     built out our rectangle area from left to right and bottom to top -> sort rectangles first
        //     then when adding a new recangle the left edge has to butt against another,
        //     which we can check by a range query [yi,bi] for min and max, whereas both have to be xi
        //     if not, then we either have a gap or an overlap
        //     at the very end, we do a final query for max and range [yi min, bi max]

        sort(rectangles.begin(),rectangles.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        // get unique y coordinates
        set<int> y_set;
        for(auto& v: rectangles) {
            y_set.insert(v[1]);
            y_set.insert(v[3]);
        }
        map<int,int> y_map;
        int y_sz = 0;
        for(int y: y_set)
            y_map[y] = y_sz++;

        // get min x coordinate
        int x_min = rectangles[0][0];

        // init segment tree
        // build(x_min,1,0,y_sz-1);
        memset(marked,false,sizeof marked);
        t[1] = make_pair(x_min,x_min);
        marked[1] = true;

        int xi, yi, ai, bi, yi_idx, bi_idx;
        pair<int,int> p;
        for(int i = 0; i < n; ++i) {
            xi = rectangles[i][0];
            yi = rectangles[i][1];
            ai = rectangles[i][2];
            bi = rectangles[i][3];
            yi_idx = y_map[yi];
            bi_idx = y_map[bi]-1; // half closed

            // range query
            p = get_min_max(1,0,y_sz-1,yi_idx,bi_idx);

            if( p.first != p.second || p.first != xi )
                return false;

            // range update
            update(1,0,y_sz-1,yi_idx,bi_idx,ai);
        }
        // finish up
        yi = rectangles[0][1];
        bi = rectangles[n-1][3];
        yi_idx = y_map[yi];
        bi_idx = y_map[bi]-1; // half closed
        p = get_min_max(1,0,y_sz-1,yi_idx,bi_idx);

        return p.first == p.second;
    }
};
