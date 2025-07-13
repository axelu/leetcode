
// 3501. Maximize Active Section with Trade II
// https://leetcode.com/problems/maximize-active-section-with-trade-ii/

class Solution {
private:
    vector<int> t; // segment tree max range query

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2],t[v*2+1]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return max(get_max(v*2, tl, tm, l, min(r, tm)), 
                   get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }    

    pair<int,int> get_r0(int l, int r, int n, unordered_map<int,int>& b, unordered_map<int,int>& e, vector<int>& nxt_lft, vector<int>& zeroblocks) {
        int r0;
        int gain = 0;
        // if r represents the end of a 0 block, we are good
        // otherwise we need to do a manual calculation for the last block
        if( r == n-1 || e.find(r) != e.end() ) {
            r0 = r;
        } else {
            // r does not represent the end of a 0 block
            // ...000...000111...1111000...0001....
            //                        r
            // we need to find the 1st 0 in our block 
            // and the zeros in the next block to our left
            // those represent one possible gain     
            int nxt1lft = nxt_lft[r]; // could be -1
            int fst_0_in_cur_block = nxt1lft + 1;
            int len_cur_block = r - fst_0_in_cur_block + 1;
            // now find 0s in the block to our left 
            //    if there is one AND l < 1st 0 in the block of 0s to our left
            int idx_cur_block = b[fst_0_in_cur_block];
            int len_lft_block = idx_cur_block > 0 ? zeroblocks[idx_cur_block-1] : 0;
            int nxtnxt0lft = nxt1lft != -1 ? nxt_lft[nxt1lft] : -1;
            // nxtnxt0lft is the rightmost 0 of the block of 0s to our left
            if( len_lft_block != 0 && l <= nxtnxt0lft ) {
                // we can have the case that l does not cover the entire block of 0s to our left
                int nxtnxtnxt0lft = nxtnxt0lft != -1 ? nxt_lft[nxtnxt0lft] + 1 : -1;
                if( nxtnxtnxt0lft != - 1 ) {
                    if( l <= nxtnxtnxt0lft ) {
                        gain = len_lft_block + len_cur_block;
                    } else {
                        gain = (nxtnxt0lft - l + 1) + len_cur_block;
                    }
                }
                // we also set r0
                r0 = nxt_lft[nxt1lft];
            } else {
                // there is no block of 0s to our left
                r0 = -1;
            }
        }
        return {r0,gain};
    }

    pair<int,int> get_l0(int l, int r, int n, unordered_map<int,int>& b, unordered_map<int,int>& e, vector<int>& nxt_rgt, vector<int>& zeroblocks) {
        int l0;
        int gain = 0;
        // if l represents the begin of a 0 block, we are good
        // otherwise we need to do a manual calculation for the 1st block
        if( l == 0 || b.find(l) != b.end() ) {
            l0 = l;
        } else {
            // l does not represent the begin of a 0 block
            // ...000...000111...1111000...0001....
            //           l              
            // we need to find the last 0 in our block 
            // and the zeros in the next block to our right
            // those represent one possible gain     
            int nxt1rgt = nxt_rgt[l];
            int lst_0_in_cur_block = nxt1rgt - 1;
            int len_cur_block = lst_0_in_cur_block -l + 1;
            // now find 0s in the block to our right 
            //    if there is one AND r ? lst 0 in the block of 0s to our right
            int idx_cur_block = e[lst_0_in_cur_block];
            int len_rgt_block = idx_cur_block < zeroblocks.size() - 1 ? zeroblocks[idx_cur_block+1] : 0;
            int nxtnxt0rgt = nxt1rgt != n ? nxt_rgt[nxt1rgt] : n;
            // nxtnxt0rgt is the leftmost 0 of the block of 0s to our right
            if( len_rgt_block != 0 && nxtnxt0rgt <= r ) {
                // we can have the case teh r does not cover the entire blco of 0s to our right
                int nxtnxtnxt0rgt = nxtnxt0rgt != n ? nxt_rgt[nxtnxt0rgt] - 1 : n;
                if( nxtnxtnxt0rgt != n ) {
                    if( nxtnxtnxt0rgt <= r ) {
                        gain = len_cur_block + len_rgt_block;
                    } else {
                        gain = len_cur_block + (r - nxtnxt0rgt + 1);
                    }
                }
                // we also set l0
                l0 = nxt_rgt[nxt1rgt];
            } else {
                // there is no block of 0s to our left
                l0 = n;
            }
        }
        return {l0,gain};
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();

        int q_sz = queries.size();
        vector<int> ans(q_sz);

        // TODO handle n == 1
 
        // pass 1 from left to right
        int ones = 0;
        int lst0 = -1;
        int lst1 = -1;
        // nxt_lft[i] if s[i] == '0' holds idx of next 1 to the left
        // nxt_lft[i] if s[i] == '1' holds idx of next 0 to the left
        vector<int> nxt_lft(n);
        vector<int> zeroblocks;
        unordered_map<int,int> b; // begin pos of a 0 block, block idx in zeroblocks
        unordered_map<int,int> e; // end pos of a 0 block, block idx in zeroblocks
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                nxt_lft[i] = lst1;
                lst0 = i;

                if( i == 0 || s[i-1] == '1' ) {
                    // a block of one or more zeros starts
                    b.insert({i, zeroblocks.size()});
                }
                if( i == n-1 || s[i+1] == '1' ) {
                    // a block of one ore more zeros ends
                    e.insert({i, zeroblocks.size()});
                    int len = i - lst1;
                    zeroblocks.push_back(len);
                }
            } else {
                nxt_lft[i] = lst0;
                lst1 = i;
                ++ones;
            }
        }

        // handle no adjacent 0 blocks
        if( zeroblocks.size() < 2 ) {
            for(int i = 0; i < q_sz; ++i)
                ans[i] = ones;
            return ans;
        }


        // pass 2 right to left
        lst0 = n;
        lst1 = n;
        vector<int> nxt_rgt(n);
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == '0' ) {
                nxt_rgt[i] = lst1;
                lst0 = i;
            } else {
                nxt_rgt[i] = lst0;
                lst1 = i;
            }
        }

        // sum adjacent pairs of 0 blocks
        // example 
        // zeroblocks               0:3  1:8  2:5  3:6
        // zeroblocksadjacentpairs       0:11 1:13 2:11
        vector<int> zeroblocksadjacentpairs;
        for(int i = 1; i < zeroblocks.size(); ++i) {
            int sum = zeroblocks[i-1] + zeroblocks[i];
            zeroblocksadjacentpairs.push_back(sum);
        }

        /*
        for(int i = 0; i < zeroblocks.size(); ++i) {
            cout << zeroblocks[i] << " ";   
        }
        cout << endl;
        for(int i = 0; i < zeroblocksadjacentpairs.size(); ++i) {
            cout << zeroblocksadjacentpairs[i] << " ";   
        }
        cout << endl;
        */

        // segment tree max range query
        t.resize(4 * zeroblocksadjacentpairs.size());
        build(zeroblocksadjacentpairs, 1, 0, zeroblocksadjacentpairs.size()-1);


        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];

            // we have the following possibilities for s[l] and s[r]
            // 1 1
            // 1 0
            // 0 1
            // 0 0

            int gain = 0;
            int l0;
            int r0;
            if( s[l] == '1' && s[r] == '1' ) {
                // find next 0 to right of l
                // find next 0 to left of right
                // get max gain in between
                l0 = nxt_rgt[l];
                r0 = nxt_lft[r];

            } else if( s[l] == '1' && s[r] == '0' ) {
                l0 = nxt_rgt[l]; 

                auto p = get_r0(l, r, n, b, e, nxt_lft, zeroblocks);
                r0 = p.first;
                gain = p.second;
 
            } else if( s[l] == '0' && s[r] == '1' ) {
                auto p = get_l0(l, r, n, b, e, nxt_rgt, zeroblocks);
                l0 = p.first;
                gain = p.second;

                r0 = nxt_lft[r];

            } else { // s[l] == '0' && s[r] == '0' ) {
                auto pl0 = get_l0(l, r, n, b, e, nxt_rgt, zeroblocks);
                l0 = pl0.first;
                gain = pl0.second;

                auto pr0 = get_r0(l, r, n, b, e, nxt_lft, zeroblocks);
                r0 = pr0.first;
                gain = max(gain, pr0.second);

            }

            if( l0 != n && r0 != -1 ) {
                int l0blockidx = b[l0]; // cout << "l0blockidx " << l0blockidx << endl;
                int r0blockidx = e[r0]; // cout << "r0blockidx " << r0blockidx << endl;
                if( l0blockidx < r0blockidx ) {
                    gain = max(gain, get_max(1, 0, zeroblocksadjacentpairs.size()-1, l0blockidx, r0blockidx-1));
                }
            } 

            ans[i] = ones + gain;
        }

        return ans;
    }
};





// passes 585/592 test cases as of 4/1/2025, then MLE (Memory Limit Exceeded)

class Solution {
private:
    struct T {
        vector<int> v;

        // examples
        // l0  l1  r0  r1              ones mx_gain
        // 1   0   1   0    0          0    0
        // 0   1   0   1    1          1    0
        // 2   0   2   2    0011       2    0
        // 3   1   1   3    1000110111 6    4

        int ones;
        int mx_gain; // best answer for the segement that the node represents

        T(vector<int> v, int ones, int mx_gain) : v(v), ones(ones), mx_gain(mx_gain) {}
    };

    T * t[400000]; // segment tree

    T * combine(T * lhs, T * rhs) {
        if( lhs == nullptr )
            return rhs;
        if( rhs == nullptr )
            return lhs;

        // we should not have the case lhs == nullptr && rhs == nullptr

        int ones = lhs->ones + rhs->ones;
        int l_mx_gain = lhs->mx_gain;
        int r_mx_gain = rhs->mx_gain;
        vector<int> v_new(lhs->v); // TODO evict middle elements we don't need
        int l_v_sz = v_new.size();

        if( lhs->v.back() != 0 && rhs->v.front() != 0 ) {
            // merging two blocks of 0s to a larger block of 0s
            v_new[l_v_sz - 1] += rhs->v.front();

            if( l_v_sz > 2 || (l_v_sz == 2 && v_new[l_v_sz - 2] != 0) )
                l_mx_gain = max(l_mx_gain, v_new[l_v_sz - 2] + v_new[l_v_sz - 1]);

            if( rhs->v.size() > 2 || (rhs->v.size() == 2 && rhs->v[1] != 0) )
                r_mx_gain = max(r_mx_gain, v_new[l_v_sz - 1] + rhs->v[1]);

            for(int i = 1; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);
            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else if( lhs->v.back() != 0 && rhs->v.front() == 0 ) {
            if( rhs->v.size() >= 2 )
                r_mx_gain = max(r_mx_gain, v_new[l_v_sz - 1] + rhs->v[1]);

            int i = rhs->v.size() == 1 ? 0 : 1;
            for(; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);
            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else if( lhs->v.back() == 0 && rhs->v.front() != 0 ) {
            if( l_v_sz >= 2 )
                l_mx_gain = max(l_mx_gain, v_new[l_v_sz - 2] + rhs->v.front());

            if( lhs->v.size() != 1 )
                v_new.pop_back();
            for(int i = 0; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);
            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else { // lhs->v.back() == 0 && rhs->v.front() == 0
            // merging two blocks of 1s

            // that block could be surrounded by 0s
            int gain = 0;
            if( lhs->v.size() >= 2 && rhs->v.size() >= 2 )
                gain = lhs->v[lhs->v.size()-2] + rhs->v[1];

            v_new.pop_back();
            if( v_new.size() == 0 ) {
                for(int i = 0; i < rhs->v.size(); ++i)
                    v_new.push_back(rhs->v[i]);
            } else {
                int i = rhs->v.size() == 1 ? 0 : 1;
                for(;i < rhs->v.size(); ++i)
                    v_new.push_back(rhs->v[i]);
            }
            return new T(v_new, ones, max({l_mx_gain, r_mx_gain, gain}));
        }
    }

    void build(string& s, int v, int tl, int tr) {
        if (tl == tr) {
            if( s[tl] == '0' )
                t[v] = new T({1},0,0);
            else
                t[v] = new T({0},1,0);
        } else {
            int tm = (tl + tr) / 2;
            build(s, v*2, tl, tm);
            build(s, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    T * get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return nullptr;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_max(v*2, tl, tm, l, min(r, tm)),
                    get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();

        int prefixSum[100001];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (int)(s[i-1]-'0');

        build(s, 1, 0, n-1);

        /*
        cout << "mx_gain " << t[1]->mx_gain << " ones " << t[1]->ones << endl;
        for(int i = 0; i < t[1]->v.size(); ++i)
            cout << t[1]->v[i] << " ";
        cout << endl;
        */

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int lactive = 0;
            if( l > 0 )
                lactive = prefixSum[l];
            int ractive = 0;
            if( r < n-1 )
                ractive = prefixSum[n] - prefixSum[r+1];

            T * t = get_max(1, 0, n-1, l, r);
            ans[i] = lactive + ( t->ones + t->mx_gain ) + ractive;
        }

        return ans;
    }
};


// slight tweak to above version to only keep max 5 elements to be merged
// that addresses memory limit, but now TLE
// passes 586/592 test cases as of 4/1/2025, then TLE


class Solution {
private:
    struct T {
        vector<int> v;

        // examples
        // l0  l1  r0  r1              ones mx_gain
        // 1   0   1   0    0          0    0
        // 0   1   0   1    1          1    0
        // 2   0   2   2    0011       2    0
        // 3   1   1   3    1000110111 6    4

        int ones;
        int mx_gain; // best answer for the segement that the node represents

        T(vector<int> v, int ones, int mx_gain) : v(v), ones(ones), mx_gain(mx_gain) {}
    };

    T * t[400000]; // segment tree

    T * combine(T * lhs, T * rhs) {
        if( lhs == nullptr )
            return rhs;
        if( rhs == nullptr )
            return lhs;

        // we should not have the case lhs == nullptr && rhs == nullptr

        int ones = lhs->ones + rhs->ones;
        int l_mx_gain = lhs->mx_gain;
        int r_mx_gain = rhs->mx_gain;
        vector<int> v_new(lhs->v); 
        int l_v_sz = v_new.size();

        if( lhs->v.back() != 0 && rhs->v.front() != 0 ) {
            // merging two blocks of 0s to a larger block of 0s
            v_new[l_v_sz - 1] += rhs->v.front();

            if( l_v_sz > 2 || (l_v_sz == 2 && v_new[l_v_sz - 2] != 0) )
                l_mx_gain = max(l_mx_gain, v_new[l_v_sz - 2] + v_new[l_v_sz - 1]);

            if( rhs->v.size() > 2 || (rhs->v.size() == 2 && rhs->v[1] != 0) )
                r_mx_gain = max(r_mx_gain, v_new[l_v_sz - 1] + rhs->v[1]);

            for(int i = 1; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);

            while( v_new.size() >= 5 ) {
                auto it = v_new.begin();
                advance(it, 2);
                v_new.erase(it);
            }
            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else if( lhs->v.back() != 0 && rhs->v.front() == 0 ) {
            if( rhs->v.size() >= 2 )
                r_mx_gain = max(r_mx_gain, v_new[l_v_sz - 1] + rhs->v[1]);

            int i = rhs->v.size() == 1 ? 0 : 1;
            for(; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);

            while( v_new.size() >= 5 ) {
                auto it = v_new.begin();
                advance(it, 2);
                v_new.erase(it);
            }

            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else if( lhs->v.back() == 0 && rhs->v.front() != 0 ) {
            if( l_v_sz >= 2 )
                l_mx_gain = max(l_mx_gain, v_new[l_v_sz - 2] + rhs->v.front());

            if( lhs->v.size() != 1 )
                v_new.pop_back();
            for(int i = 0; i < rhs->v.size(); ++i)
                v_new.push_back(rhs->v[i]);

            while( v_new.size() >= 5 ) {
                auto it = v_new.begin();
                advance(it, 2);
                v_new.erase(it);
            }

            return new T(v_new, ones, max(l_mx_gain, r_mx_gain));

        } else { // lhs->v.back() == 0 && rhs->v.front() == 0
            // merging two blocks of 1s

            // that block could be surrounded by 0s
            int gain = 0;
            if( lhs->v.size() >= 2 && rhs->v.size() >= 2 )
                gain = lhs->v[lhs->v.size()-2] + rhs->v[1];

            v_new.pop_back();
            if( v_new.size() == 0 ) {
                for(int i = 0; i < rhs->v.size(); ++i)
                    v_new.push_back(rhs->v[i]);
            } else {
                int i = rhs->v.size() == 1 ? 0 : 1;
                for(;i < rhs->v.size(); ++i)
                    v_new.push_back(rhs->v[i]);
            }

            while( v_new.size() >= 5 ) {
                auto it = v_new.begin();
                advance(it, 2);
                v_new.erase(it);
            }

            return new T(v_new, ones, max({l_mx_gain, r_mx_gain, gain}));
        }
    }

    void build(string& s, int v, int tl, int tr) {
        if (tl == tr) {
            if( s[tl] == '0' )
                t[v] = new T({1},0,0);
            else
                t[v] = new T({0},1,0);
        } else {
            int tm = (tl + tr) / 2;
            build(s, v*2, tl, tm);
            build(s, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    T * get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return nullptr;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_max(v*2, tl, tm, l, min(r, tm)),
                    get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();

        int prefixSum[100001];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (int)(s[i-1]-'0');

        build(s, 1, 0, n-1);

        /*
        cout << "mx_gain " << t[1]->mx_gain << " ones " << t[1]->ones << endl;
        for(int i = 0; i < t[1]->v.size(); ++i)
            cout << t[1]->v[i] << " ";
        cout << endl;
        */

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int lactive = 0;
            if( l > 0 )
                lactive = prefixSum[l];
            int ractive = 0;
            if( r < n-1 )
                ractive = prefixSum[n] - prefixSum[r+1];

            T * t = get_max(1, 0, n-1, l, r);
            ans[i] = lactive + ( t->ones + t->mx_gain ) + ractive;
        }

        return ans;
    }
};
