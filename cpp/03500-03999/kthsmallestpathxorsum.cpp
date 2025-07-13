
// 3590. Kth Smallest Path XOR Sum
// https://leetcode.com/problems/kth-smallest-path-xor-sum/

// inspired by https://leetcode.com/problems/kth-smallest-path-xor-sum/solutions/6881964/for-the-people-looking-for-java-solution

class Solution {
private:
    vector<vector<int>> t;
    vector<int> ans;
    vector<int> * _vals;
    vector<vector<vector<int>>> _queries;

    const int size = 17; // per constraint max val = 100000 decimal -> 17 digits binary

    struct Trie {
        struct Trie* children[2]; // 0 unset bit, 1 set bit
        int cnt;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;
        tn->cnt = 0;
        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int x, Trie * dic) {
        struct Trie* tn = dic;

        for(int i = size-1; i >= 0; --i) {
            int idx = x & (1<<i) ? 1 : 0;
            if( !tn->children[idx] )
                tn->children[idx] = init();

            ++tn->cnt;
            tn = tn->children[idx];
        }

        return;
    }

    bool search(int x, Trie * dic) {
        struct Trie* tn = dic;

        for(int i = size-1; i >= 0; --i) {
            int idx = x & (1<<i) ? 1 : 0;
            if( !tn->children[idx] )
                return false;

            tn = tn->children[idx];
        }

        return true;
    }

    Trie * merge(Trie * p, Trie * c) {
        if( !p )
            return c;
        if( !c )
            return p;

        for(int i = 0; i < 2; ++i) {
            if( !p->children[i] )
                p->children[i] = c->children[i];
            else
                p->children[i] = merge(p->children[i], c->children[i]);
        }

        p->cnt = 0;
        if( p->children[0] )
            p->cnt += p->children[0]->cnt == 0 ? 1 : p->children[0]->cnt;
        if( p->children[1] )
            p->cnt += p->children[1]->cnt == 0 ? 1 : p->children[1]->cnt;

        return p;
    }

    int findkth(int k, Trie * dic) {
        if( dic->cnt < k)
            return -1;

        Trie * tn = dic;
        int ret = 0;
        for(int i = size-1; i >=0 ; --i) {
            if( tn->children[0] && (tn->children[0]->cnt >= k || k == 1) ) {
                tn = tn->children[0];
            } else {
                ret |= (1<<i);
                k -= !tn->children[0] ? 0 : tn->children[0]->cnt;
                tn = tn->children[1];
            }
        }

        return ret;
    }

    Trie * dfs(int u, int p_xor) {
        int u_xor = p_xor ^ _vals->at(u);

        Trie * p = init();

        for(int v :t[u]) {
            Trie * c = dfs(v, u_xor);
            p = merge(p,c);
        }

        if( !search(u_xor, p) )
            add(u_xor, p);

        // ans all questions for u
        for(auto q: _queries[u]) {
            int q_idx = q[0];
            int k = q[1];

            ans[q_idx] = findkth(k, p);
        }

        return p;
    }


public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        int n = par.size(); // par.size() == vals.size()
        _vals = &vals;

        // undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1
        t.resize(n);
        for(int v = 1; v < n; ++v) {
            int u = par[v];
            t[u].push_back(v);
        }

        int q_sz = queries.size();
        ans.assign(q_sz, -1);
        _queries.resize(n);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int k = queries[i][1];
            _queries[u].push_back({i,k});
        }

        dfs(0, 0);
        return ans;
    }
};





// also passes 592/595 test cases as of 6/27/2025, then TLE
// reduced that case to about half of the queries, it completes in abut 2s with correct result

class Solution {
private:
    vector<int> * _vals;

    vector<vector<int>> g;

    int timer;
    vector<int> tin;
    vector<int> cnt;
    vector<int> arr;

    int dfs(int u, int p_xor) {
        int u_xor = p_xor ^ _vals->at(u);

        arr[timer] = u_xor;
        tin[u] = timer++;

        int ret = 1;

        for(int v :g[u])
            ret += dfs(v, u_xor);

        return cnt[u] = ret;
    }

    vector<int> t[200000]; // segment tree, merge sort tree (distinct), range query to get sorted segment

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {arr[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            
            // merge
            int i = 0, j = 0;
            int a_sz = t[v*2].size();
            int b_sz = t[v*2+1].size();
            while( i < a_sz && j < b_sz ) {
                if( t[v*2][i] < t[v*2+1][j] ) {
                    t[v].push_back(t[v*2][i]);
                    ++i;
                } else if( t[v*2][i] == t[v*2+1][j] ) {
                    t[v].push_back(t[v*2][i]);
                    ++i;
                    ++j;
                } else { // t[v*2][i] > t[v*2+1][j]
                    t[v].push_back(t[v*2+1][j]);
                    ++j;
                }
            }
            while( i < a_sz ) {
                t[v].push_back(t[v*2][i]);
                ++i;
            }
            while( j < b_sz ) {
                t[v].push_back(t[v*2+1][j]);
                ++j;
            }
        }
        return;
    }

    vector<int> query(int v, int tl, int tr, int l, int r) {
        if (l > r )
            return {};

        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;

        vector<int> a = query(v*2, tl, tm, l, min(r, tm));
        vector<int> b = query(v*2+1, tm+1, tr, max(l, tm+1), r);
        // merge
        vector<int> c;
        int i = 0, j = 0;
        int a_sz = a.size();
        int b_sz = b.size();
        while( i < a_sz && j < b_sz ) {
            if( a[i] < b[j] ) {
                c.push_back(a[i]);
                ++i;
            } else if( a[i] == b[j] ) {
                c.push_back(a[i]);
                ++i;
                ++j;
            } else { // a[i] > b[j]
                c.push_back(b[j]);
                ++j;
            }
        }
        while( i < a_sz ) {
            c.push_back(a[i]);
            ++i;
        }
        while( j < b_sz ) {
            c.push_back(b[j]);
            ++j;
        }
        return c;
    }

public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        int n = par.size(); // par.size() == vals.size()
        _vals = &vals;

        // undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1
        g.resize(n);
        for(int v = 1; v < n; ++v) {
            int u = par[v];
            g[u].push_back(v);
        }

        // pass 1 
        // record for each node its discovery time using preorder traversal
        // record for each node the number of nodes in its subtree (including the node itself)
        // record each XOR path sum in order

        timer = 0;
        tin.resize(n);
        cnt.resize(n);
        arr.resize(n);
        dfs(0, 0);

        // create a segment tree that holds sorted unique path XOR sums for each segment
        // a segment is the discovery time of node + (number of nodes it its subtree) - 1 
        build(1, 0, n-1);

        int q_sz = queries.size();
        vector<vector<vector<int>>> _queries(n);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int k = queries[i][1];
            _queries[u].push_back({k,i});
        }
        for(int u = 0; u < n; ++u)
            sort(_queries[u].begin(), _queries[u].end());

        vector<int> ans(q_sz, -1);
        // process queries
        for(int u = 0; u < n; ++u) {
            if( !_queries[u].empty() ) {
                // sorted list of unique xor path sums in the subtree of u
                vector<int> nums = query(1, 0, n-1, tin[u], tin[u] + cnt[u] - 1);
                int nums_sz = nums.size();

                for(auto ki: _queries[u]) {
                    int k = ki[0] - 1;
                    int q_idx = ki[1];
                    if( k >= nums_sz )
                        break;
                    ans[q_idx] = nums[k];
                }
            }
        }

        return ans;
    }
};



// passes 592/595 test cases as of 6/26/2025, then TLE
// test case 592 in browser also TLE,
// which is obvious, as worst case is 50000 * 50000, so this does not work


class Solution {
private:
    vector<vector<int>> t;

    vector<int> ans;
    vector<int> * _vals;
    vector<vector<vector<int>>> _queries;

    set<int> dfs(int u, int p_xor) {
        int u_xor = p_xor ^ _vals->at(u);
        set<int> st{u_xor};

        for(int v :t[u]) {
            set<int> t = dfs(v, u_xor);
            for(int xr: t)
                st.insert(xr);
        }

        int st_sz = st.size();

        // ans all questions for u
        for(auto q: _queries[u]) {
            int q_idx = q[0];
            int k = q[1];
            if( k > st_sz )
                continue;

            auto it = st.begin();
            advance(it, k-1);
            ans[q_idx] = *it;
        }

        return st;
    }


public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        int n = par.size(); // par.size() == vals.size()
        _vals = &vals;

        // undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1
        t.resize(n);
        for(int v = 1; v < n; ++v) {
            int u = par[v];
            t[u].push_back(v);
        }

        int q_sz = queries.size();
        ans.assign(q_sz, -1);
        _queries.resize(n);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int k = queries[i][1];
            _queries[u].push_back({i,k});
        }

        dfs(0, 0);
        return ans;
    }
};
