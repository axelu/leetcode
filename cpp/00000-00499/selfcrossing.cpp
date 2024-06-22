
// 335. Self Crossing
// https://leetcode.com/problems/self-crossing/



class Solution {
private:
    set<int> * ht; // segment tree, lazy [range update] propagation
    bool * hmarked;
    set<int> * vt; // segment tree, lazy [range update] propagation
    bool * vmarked;

    void push(int v, set<int> * t, bool * marked) {
        if( marked[v] ) {
            // left child
            for(int i: t[v])
               t[v*2].insert(i); 
            marked[v*2] = true;
            
            // right child
            for(int i: t[v])
               t[v*2+1].insert(i); 
            marked[v*2+1] = true;
                        
            marked[v] = false;
        }
        return;
    }

    // range update
    void update(int v, int tl, int tr, int l, int r, int new_val, set<int> * t, bool * marked) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v].insert(new_val);
            marked[v] = true;
        } else {
            push(v,t,marked);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), new_val, t, marked);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val, t, marked);
        }
    }    
    
    // point query
    set<int> get(int v, int tl, int tr, int pos, set<int> * t, bool * marked) {
        if( tl == tr ) {
            return t[v];
        }
        push(v,t,marked);
        int tm = (tl + tr) / 2;
        if (pos <= tm)  // go left 
            return get(v*2, tl, tm, pos, t, marked);
        else            // go right
            return get(v*2+1, tm+1, tr, pos, t, marked);
    }    

    bool does_intersect(set<int>& st, int s, int e) {
        auto lb = st.lower_bound(s);
        if( lb == st.end() || *lb > e )
            return false;
        
        return true;
    }
    
public:
    bool isSelfCrossing(vector<int>& distance) {
        int n = distance.size();
        if( n <= 2 )
            return false;
        
        // 1 <= distance.length <= 1e5
        // distance[0] north, distance[1] west, distance[2] south, distance[3] east, ... repeat
        // worst case distinct x and y values
        // distance.size() == 100000, then in a block of 4 distances, we could have 2 distinct x's and 2 distinct y's added
        // -> total 50001 distinct x's and 50001 distinct y's (includes our starting point 0,0)
        
        set<long> x_set{0};  // we are starting at x = 0
        long x = 0L;          // we are starting at x = 0
        set<long> y_set{0};  // we are starting at y = 0
        long y = 0L;          // we are starting at y = 0
        for(int i = 0; i < n; ++i) {
            int dir = i % 4;
            if( dir == 0 ) {
                // vertical move north
                y += (long)distance[i]; 
                y_set.insert(y);
            } else if( dir == 1 ) {
                // horizontal move west
                x -= (long)distance[i];
                x_set.insert(x);
            } else if( dir == 2 ) {
                // vertical move south
                y -= (long)distance[i];
                y_set.insert(y);
            } else {
                // horizontal move east
                x += (long)distance[i];
                x_set.insert(x);
            }
        }
        // if we ended back at 0,0, we also intersected
        if( x == 0L && y == 0L )
            return true;
        
        // ht segment tree with horizontal lines
        int x_sz = 0;
        unordered_map<long,int> x_map;
        for(long i: x_set)
            x_map[i] = x_sz++;
        set<int> _ht[4*x_sz]; ht = _ht;
        bool _hmarked[4*x_sz]; memset(_hmarked,false,sizeof _hmarked); hmarked = _hmarked;
        
        // vt segment tree with vertical lines
        int y_sz = 0;
        unordered_map<long,int> y_map;
        for(long i: y_set)
            y_map[i] = y_sz++;
        set<int> _vt[4*y_sz]; vt = _vt;
        bool _vmarked[4*y_sz]; memset(_vmarked,false,sizeof _vmarked); vmarked = _vmarked;
        
        
        x = 0L;
        y = 0L;
        // add move 0 (vertical, north) to the vertial [line] tree
        long y_new = y + (long)distance[0];
        update(1, 0, y_sz-1, y_map[y], y_map[y_new], x_map[x], vt, vmarked);
        y = y_new;
        
        // add move 1 (horizontal, west) to the horizontal [line] tree
        long x_new = x - (long)distance[1];
        update(1, 0, x_sz-1, x_map[x_new], x_map[x], y_map[y], ht, hmarked);
        x = x_new;
        
        for(int i = 2; i < n-1; ++i) {
        
            // before adding line 'i' ask:
            //   is there anything that line 'i+1' intersects with
            
            int dir = i % 4;
            if( dir == 0 ) {
                // vertical move north
                // start y, end y_new at x-coordinate x
                y_new = y + (long)distance[i];
                
                // the move after this would be horizontal west
                // start = x_new, end = x at height y_new 
                // ask stabbing question to vertical segment tree
                x_new = x - (long)distance[i+1];
                auto st = get(1, 0, y_sz-1, y_map[y_new], vt, vmarked);
                if( does_intersect(st, x_map[x_new], x_map[x]) )
                    return true;
            
                update(1, 0, y_sz-1, y_map[y], y_map[y_new], x_map[x], vt, vmarked);
                y = y_new;

            } else if( dir == 1 ) {
                // horizontal move west
                // start x_new, end x at height y
                x_new = x - (long)distance[i];
                
                // the move after this would be vertical south
                // start = y_new, end = y at x-coordinate x_new
                // ask stabbing question to horizontal segment tree
                y_new = y - (long)distance[i+1];
                auto st = get(1, 0, x_sz-1, x_map[x_new], ht, hmarked);
                if( does_intersect(st, y_map[y_new], y_map[y]) )
                    return true;
                
                update(1, 0, x_sz-1, x_map[x_new], x_map[x], y_map[y], ht, hmarked);
                x = x_new;
                
            } else if( dir == 2 ) {
                // vertical move south
                // start y_new, end y at x-coordinate x
                y_new = y - (long)distance[i];
                
                // the move after this would be horizontal east
                // start = x, end = x_new at height y_new 
                // ask stabbing question to vertical segment tree
                x_new = x + (long)distance[i+1];
                auto st = get(1, 0, y_sz-1, y_map[y_new], vt, vmarked);
                if( does_intersect(st, x_map[x], x_map[x_new]) )
                    return true;
            
                update(1, 0, y_sz-1, y_map[y_new], y_map[y], x_map[x], vt, vmarked);
                y = y_new;
            
            } else {
                // horizontal move east
                // start x, end x_new at height y
                x_new = x + (long)distance[i];
                
                // the move after this would be vertical north
                // start = y, end = y_new at x-coordinate x_new
                // ask stabbing question to horizontal segment tree
                y_new = y + (long)distance[i+1];
                auto st = get(1, 0, x_sz-1, x_map[x_new], ht, hmarked);
                if( does_intersect(st, y_map[y], y_map[y_new]) )
                    return true;
                
                update(1, 0, x_sz-1, x_map[x], x_map[x_new], y_map[y], ht, hmarked);
                x = x_new;
            }
        }
        
        return false;
    }
};

