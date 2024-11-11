
// 3229. Minimum Operations to Make Array Equal to Target
// https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/



class Solution {
private:
    vector<int> t[200000]; // segment tree memory efficient indexing; idx 0: min, remainng the positions of min

    vector<int> combine(vector<int>& a, vector<int>& b) {
        int mina = a[0];
        int minb = b[0];
        if( mina < minb ) {
            return a;
        } else if( mina > minb ) {
            return b;
        } else {
            vector<int> ret(a);
            for(int i = 1; i < b.size(); ++i)
                ret.push_back(b[i]);
            return ret;
        }
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {a[tl],tl};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    vector<int> get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {INT_MAX};
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }
    
    int n;
    
    long long solve(vector<int>& v, int s, int e, int offset) {
        // cout << "solve s " << s << " e " << e << " offset " << offset << endl;
        if( e - s == 0 )
            return v[s] - offset;
        
        // we apply operation min[s,e] - offset times
        
        auto vmin = get(1,0,n-1,s,e);
        if( e - s + 1 + 1 == vmin.size() )
            return vmin[0] - offset;
        
        int mn = vmin[0];
        
        long long ret = mn - offset;
        
        // new offset = mn
        
        // split interval
        for(int i = 1; i < vmin.size(); ++i) {
            if( i == 1 ) {
                // is there something to our left?
                if( vmin[i] > s )
                    ret += solve(v, s, vmin[i]-1, mn);
            }
            
            // is there something in between?
            if( i > 1 && vmin[i-1] + 1 < vmin[i] )
                ret += solve(v, vmin[i-1]+1, vmin[i]-1, mn);
            
            if( i == vmin.size() - 1 ) {
                // is there something to our right?
                if( vmin[i] < e )
                    ret += solve(v, vmin[i]+1, e, mn);
            }
        }
        
        return ret;
    }

    long long solve(vector<int>& v, int s, int e, set<int>& unique) {
        // cout << "solve s " << s << " e " << e << endl;

        // line sweep
        
        map<int,int> mp;
        int idx = 0;
        for(auto it = unique.begin(); it != unique.end(); ++it) {
            // cout << *it << " ";
            mp[*it] = idx++;
        }
        // cout << endl;
        
        int line[unique.size()+1];memset(line,0,sizeof line);
        int pend;
        for(int i = 0, k = s; k <= e; ++i, ++k) {
            int end = mp[v[k]]+1;
            if( i == 0 ) {
                ++line[0];    
                --line[end];
            } else {
                if( pend < end ) {
                    ++line[pend];
                    --line[end];
                }
            }
            pend = end;
        }
        /*
        for(int i = 0; i < unique.size()+1; ++i)
            cout << line[i] << " ";
        cout << endl;
        */
        long long ret = 0LL;
        idx = 0;
        long long f = 0;
        int pre = 0;
        for(auto it = unique.begin(); it != unique.end(); ++it) {
            f += line[idx++];
            ret += f * (long long)(*it-pre);
            pre = *it;
        }
        
        return ret;
    }
    
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        n = nums.size(); //  nums.length == target.length
        
        // idea
        // create new array that has the differences at each position
        // then process on block at a time
        // a block is a subarray where all differences are either positive or negative
        // when processing this block it may break into one or more blocks - interval split
        // process those blocks recursively
        // then continue
        
        long long ans = 0LL;
        
        vector<int> v;
        int mode = 0; // 0 undetermined, -1 nums > target, 1 nums > target
        vector<vector<int>> intervals;
        vector<set<int>> uniques;
        set<int> unique;
        int i = 0;
        int s, e;
        for(int j = 0; j < n; ++j) {
            int diff = target[j] - nums[j];
            if( mode == 0 ) {
                // we are starting a new block
                // i will be equal j
                if( diff == 0 ) {
                    i = j + 1;
                    v.push_back(0);

                } else if( diff < 0 ) {
                    mode = -1;
                    v.push_back(-diff);
                    unique.insert(-diff);
                    
                } else { // diff > 0 
                    mode = 1;
                    v.push_back(diff);
                    unique.insert(diff);
                    
                }
            } else if( mode == -1 ) {
                if( diff == 0 ) {
                    // mode is ending
                    mode = 0;
                    intervals.push_back({i,j-1});
                    uniques.push_back(unique);
                    unique.clear();
                    i = j + 1;
                    v.push_back(0);
        
                } else if( diff < 0 ) {
                    v.push_back(-diff);
                    unique.insert(-diff);
                
                } else { //diff > 0 
                    // mode is ending, new mode is starting
                    mode = 1;
                    intervals.push_back({i,j-1});
                    uniques.push_back(unique);
                    unique.clear();
                    i = j + 1;
                    i = j;
                    v.push_back(diff);
                    unique.insert(diff);
                    
                }
            } else { // mode == 1
                if( diff == 0 ) {
                    // mode is ending
                    mode = 0;
                    intervals.push_back({i,j-1});
                    uniques.push_back(unique);
                    unique.clear();
                    i = j + 1;
                    i = j + 1;
                    v.push_back(0);
                    
                } else if( diff < 0 ) {
                    // mode is ending, new mode is starting
                    mode = -1;
                    intervals.push_back({i,j-1});
                    uniques.push_back(unique);
                    unique.clear();
                    i = j + 1;
                    i = j;
                    v.push_back(-diff);
                    unique.insert(-diff);
                    
                } else { // diff > 0
                    v.push_back(diff);
                    unique.insert(diff);
                }
            }
        }
        // finish up
        if( i < n ) {
            intervals.push_back({i,n-1});
            uniques.push_back(unique);
        }
        
        /*
        for(int x: v)
            cout << x << " ";
        cout << endl;
        */
        
        // build(v,1,0,n-1);
        
        for(int i = 0; i < intervals.size(); ++i) {
            int s = intervals[i][0];
            int e = intervals[i][1];
            
            // ans += solve(v, s, e, 0LL);
            ans += solve(v,s,e,uniques[i]);
        }
        
        return ans;
    }
};




// passes 551/554 test cases, then TLE
// running the failing test case completes correctly in about 1800ms, which is obviously to slow

class Solution {
private:
    vector<int> t[200000]; // segment tree memory efficient indexing; idx 0: min, remainng the positions of min

    vector<int> combine(vector<int>& a, vector<int>& b) {
        int mina = a[0];
        int minb = b[0];
        if( mina < minb ) {
            return a;
        } else if( mina > minb ) {
            return b;
        } else {
            vector<int> ret(a);
            for(int i = 1; i < b.size(); ++i)
                ret.push_back(b[i]);
            return ret;
        }
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {a[tl],tl};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    vector<int> get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {INT_MAX};
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

    int n;

    long long solve(vector<int>& v, int s, int e, int offset) {
        // cout << "solve s " << s << " e " << e << " offset " << offset << endl;
        if( e - s == 0 )
            return v[s] - offset;

        // we apply operation min[s,e] - offset times

        auto vmin = get(1,0,n-1,s,e);
        if( e - s + 1 + 1 == vmin.size() )
            return vmin[0] - offset;

        int mn = vmin[0];

        long long ret = mn - offset;

        // new offset = mn

        // split interval
        for(int i = 1; i < vmin.size(); ++i) {
            if( i == 1 ) {
                // is there something to our left?
                if( vmin[i] > s )
                    ret += solve(v, s, vmin[i]-1, mn);
            }

            // is there something in between?
            if( i > 1 && vmin[i-1] + 1 < vmin[i] )
                ret += solve(v, vmin[i-1]+1, vmin[i]-1, mn);

            if( i == vmin.size() - 1 ) {
                // is there something to our right?
                if( vmin[i] < e )
                    ret += solve(v, vmin[i]+1, e, mn);
            }
        }

        return ret;
    }

public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        n = nums.size(); //  nums.length == target.length

        // idea
        // create new array that has the differences at each position
        // then process on block at a time
        // a block is a subarray where all differences are either positive or negative
        // when processing this block it may break into one or more blocks - interval split
        // process those blocks recursively
        // then continue

        long long ans = 0LL;

        vector<int> v;
        int mode = 0; // 0 undetermined, -1 nums > target, 1 nums > target
        vector<vector<int>> intervals;
        int i = 0;
        int s, e;
        for(int j = 0; j < n; ++j) {
            int diff = target[j] - nums[j];
            if( mode == 0 ) {
                // we are starting a new block
                // i will be equal j
                if( diff == 0 ) {
                    i = j + 1;
                    v.push_back(0);

                } else if( diff < 0 ) {
                    mode = -1;
                    v.push_back(-diff);

                } else { // diff > 0
                    mode = 1;
                    v.push_back(diff);

                }
            } else if( mode == -1 ) {
                if( diff == 0 ) {
                    // mode is ending
                    mode = 0;
                    intervals.push_back({i,j-1});
                    i = j + 1;
                    v.push_back(0);

                } else if( diff < 0 ) {
                    v.push_back(-diff);

                } else { //diff > 0
                    // mode is ending, new mode is starting
                    mode = 1;
                    intervals.push_back({i,j-1});
                    i = j;
                    v.push_back(diff);

                }
            } else { // mode == 1
                if( diff == 0 ) {
                    // mode is ending
                    mode = 0;
                    intervals.push_back({i,j-1});
                    i = j + 1;
                    v.push_back(0);

                } else if( diff < 0 ) {
                    // mode is ending, new mode is starting
                    mode = -1;
                    intervals.push_back({i,j-1});
                    i = j;
                    v.push_back(-diff);

                } else { // diff > 0
                    v.push_back(diff);
                }
            }
        }
        // finish up
        if( i < n )
            intervals.push_back({i,n-1});

        /*
        for(int x: v)
            cout << x << " ";
        cout << endl;
        */

        build(v,1,0,n-1);

        for(int i = 0; i < intervals.size(); ++i) {
            int s = intervals[i][0];
            int e = intervals[i][1];

            ans += solve(v, s, e, 0LL);
        }

        return ans;
    }
};
