
// 3569. Maximize Count of Distinct Primes After Split
// https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/


// initialize once
bool init = false;
bool is_prime[100001];

class Solution {
private:
   bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

    int t[200000];      // segment tree (max), lazy propagation, range addition, range query
    int lazy[200000];

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    // get max
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INT_MIN;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, min(r, tm)),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    void process_prime_removal(int n, map<int,set<int>>& indices, int prime, int idx) {
        if( indices[prime].size() > 2 ) {
            int l = *(indices[prime].begin());
            int r = *(indices[prime].rbegin());

            indices[prime].erase(idx);

            if( l == idx ) {
                r = *(indices[prime].begin()) - 1;
                update(1, 0, n-1, l, r, -1);
            } else if( r == idx ) {
                l = *(indices[prime].rbegin()) + 1;
                update(1, 0, n-1, l, r, -1);
            }

        } else if( indices[prime].size() == 2 ) {
            // idx must either be the begin or end
            // in either case, the entire range will be removed
            int l = *(indices[prime].begin());
            int r = *(indices[prime].rbegin());
            indices[prime].erase(idx);
            update(1, 0, n-1, l, r, -1);

        } else { // indices[prime].size() == 1
            // idx must be the remaining index
            indices.erase(prime);
        }

        return;
    }

    void process_prime_addition(int n, map<int,set<int>>& indices, int prime, int idx) {
        if( indices[prime].size() == 1 ) {
            int t = *(indices[prime].begin());
            int l = min(idx, t);
            int r = max(idx, t);
            update(1, 0, n-1, l, r, 1);

        } else if( indices[prime].size() > 1 ) {
            int l = *(indices[prime].begin());
            int r = *(indices[prime].rbegin());
            if( idx < l ) {
                r = l-1;
                l = idx;
                update(1, 0, n-1, l, r, 1);
            } else if( idx > r ) {
                l = r+1;
                r = idx;
                update(1, 0, n-1, l, r, 1);
            }
        }
        indices[prime].insert(idx);

        return;
    }
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        if( !init ) {
            init = true;
            for(int i = 0; i <= 100000; ++i)
                is_prime[i] = isPrime(i);
        }

        memset(t,0,sizeof t);
        memset(lazy,0,sizeof lazy);

        int n = nums.size();

        // keep track of primes in nums
        map<int,set<int>> indices;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if( is_prime[x] )
                indices[x].insert(i);
        }

        for(auto it = indices.begin(); it != indices.end(); ++it) {
            if( it->second.size() > 1 ) {
                int l = *(it->second.begin());
                int r = *(it->second.rbegin());
                update(1, 0, n-1, l, r, 1);
            }
        }

        // process queries
        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int idx = queries[i][0];
            int cur_val = nums[idx];
            int new_val = queries[i][1];

            if( cur_val == new_val ) {
                ans[i] = t[1] + indices.size();
                continue;
            }

            nums[idx] = new_val;

            if( !is_prime[cur_val] && !is_prime[new_val] ) {
                // do nothing
            } else if( is_prime[cur_val] && !is_prime[new_val] ) {
                process_prime_removal(n, indices, cur_val, idx);
            } else if( !is_prime[cur_val] && is_prime[new_val] ) {
                process_prime_addition(n, indices, new_val, idx);
            } else { // is_prime[cur_val] && is_prime[new_val]
                process_prime_removal(n, indices, cur_val, idx);
                process_prime_addition(n, indices, new_val, idx);
            }

            ans[i] = t[1] + indices.size();
        }

        return ans;
    }
};
