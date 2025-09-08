
// 3636. Threshold Majority Queries
// https://leetcode.com/problems/threshold-majority-queries/



// based on hints
// https://cp-algorithms.com/data_structures/sqrt_decomposition.html
// square root decomposition (sqrt decomposition)
// https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm
// Mo's algorithm - find the mode of a range

class Solution {
// private:

/*
    map<int,int> dic; // val, count

    struct PairCmp {
        bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
            // pair.first = count; pair.second = val
            if( a.first < b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second > b.second ) {
                    return true;
                }
            }
            return false;
        }
    };

    set<pair<int,int>, PairCmp> st; // pair: count, val

    void remove(int val) {
        // get current count
        int cur_count = dic[val];

        // decrease count
        --dic[val];
        //st.erase({cur_count, val});
        //if( dic[val] != 0 )
        //    st.insert({--cur_count, val});
        // if( dic[val] == 0 )
        //    dic.erase(val);

        return;
    }
    
    void add(int val) {
        // get current count
        int cur_count = dic[val];

        // increase count
        ++dic[val];
        //if( cur_count > 0 )
        //    st.erase({cur_count, val});
        //st.insert({++cur_count, val});

        return;
    }     
    
    // int get_answer();  // TODO: extract the current answer of the data structure
*/

public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        int block_size = (int)sqrt(n + .0) + 1; // block size and number of blocks

        int q_sz = queries.size();
        vector<int> ans(q_sz, -1);

        // pre-process queries
        struct Query {
            int l, r, threshold, idx, block_size;
            bool operator<(Query other) const
            {
                return make_pair(l / block_size, r) <
                    make_pair(other.l / block_size, other.r);
            }
        };
        vector<Query> _queries(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int threshold = queries[i][2];
            _queries[i] = {l, r, threshold, i, block_size};
        }
        
        sort(_queries.begin(), _queries.end());

        // process queries
        map<int,int> dic; // val, count
        int cur_l = 0;
        int cur_r = -1; 
        int val;
        int cur_count;

        struct PairCmp {
            bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
                // pair.first = count; pair.second = val
                if( a.first < b.first ) {
                    return true;
                } else if( a.first == b.first ) {
                    if( a.second > b.second ) {
                        return true;
                    }
                }
                return false;
            }
        };

        set<pair<int,int>, PairCmp> st; // pair: count, val

        for(Query q: _queries) {
            //cout << "cur_l " << cur_l << " cur_r " << cur_r << endl;
            //cout << "q.l.  " << q.l <<   " q.r   " << q.r << endl;

            while (cur_l > q.l) {
                cur_l--;
                // add(nums[cur_l]);

                val = nums[cur_l];
                cur_count = dic[val]++;            
                if( cur_count > 0 )
                    st.erase({cur_count, val});
                st.insert({++cur_count, val});
            }
            while (cur_r < q.r) {
                cur_r++;
                // add(nums[cur_r]);

                val = nums[cur_r];
                cur_count = dic[val]++;            
                if( cur_count != 0 ) // must be > zero
                    st.erase({cur_count, val});
                st.insert({++cur_count, val});
            }
            while (cur_l < q.l) {
                // remove(nums[cur_l]);

                val = nums[cur_l];
                cur_count = dic[val]--;
                st.erase({cur_count, val});
                if( --cur_count != 0 )
                    st.insert({cur_count, val});

                cur_l++;
            }
            while (cur_r > q.r) {
                // remove(nums[cur_r]);

                val = nums[cur_r];
                cur_count = dic[val]--;
                st.erase({cur_count, val});
                if( --cur_count != 0 )
                    st.insert({cur_count, val});

                cur_r--;
            }

            // answers[q.idx] = get_answer();
            if( st.rbegin()->first >= q.threshold )
                ans[q.idx] = st.rbegin()->second;
        }

        return ans;
    }
};




// passes 552/559 test cases, the TLE as of 8/4/2025
// case 553 runs in about ~2700ms, correct result, but obviously to slow

class Solution {
private:
    struct T {
        map<int,int> dic; // val, count
        int mx_freq;
        int most_freq_val;
        T() : dic({}), mx_freq(-1), most_freq_val(-1) {}
        T(map<int,int> dic, int mx_freq, int most_freq_val) : dic(dic), mx_freq(mx_freq), most_freq_val(most_freq_val) {}
    };

    T t[20000]; // segment tree, memory efficient implementation, range query

    T combine(T& a, T& b) {
        int mx_freq = a.mx_freq;
        int most_freq_val = a.most_freq_val;
        map<int,int> dic(a.dic);
        for(auto& pb: b.dic) {
            auto p = dic.insert(pb);
            if( !p.second )
                p.first->second += pb.second;

            if( p.first->second == mx_freq ) {
                if( pb.first < most_freq_val )
                    most_freq_val = pb.first;
            } else if( p.first->second > mx_freq ) {
                mx_freq = p.first->second;
                most_freq_val = p.first->first;
            }
        }
        return T(dic, mx_freq, most_freq_val);
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = T({{a[tl],1}}, 1, a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // range query (sum)
    T get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return T();
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }


public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        build(nums, 1, 0, n-1);

        // process queries
        int q_sz = queries.size();
        vector<int> ans(q_sz, -1);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int threshold = queries[i][2];

            T res = get(1, 0, n-1, l, r);
            if( res.mx_freq >= threshold )
                ans[i] = res.most_freq_val;
        }

        return ans;
    }
};

// changing to pointers virtually no difference in regards to runtime
class Solution {
private:
    struct T {
        map<int,int> dic; // val, count
        int mx_freq;
        int most_freq_val;
        T() : dic({}), mx_freq(-1), most_freq_val(-1) {}
        T(map<int,int> dic, int mx_freq, int most_freq_val) : dic(dic), mx_freq(mx_freq), most_freq_val(most_freq_val) {}
    };

    T * t[20000]; // segment tree, memory efficient implementation, range query

    T * combine(T * a, T * b) {
        int mx_freq = a->mx_freq;
        int most_freq_val = a->most_freq_val;
        map<int,int> dic(a->dic);
        for(auto& pb: b->dic) {
            auto p = dic.insert(pb);
            if( !p.second )
                p.first->second += pb.second;

            if( p.first->second == mx_freq ) {
                if( pb.first < most_freq_val )
                    most_freq_val = pb.first;
            } else if( p.first->second > mx_freq ) {
                mx_freq = p.first->second;
                most_freq_val = p.first->first;
            }
        }
        return new T(dic, mx_freq, most_freq_val);
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = new T({{a[tl],1}}, 1, a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // range query (sum)
    T * get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return new T();
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }


public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        build(nums, 1, 0, n-1);

        // process queries
        int q_sz = queries.size();
        vector<int> ans(q_sz, -1);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int threshold = queries[i][2];

            T * res = get(1, 0, n-1, l, r);
            if( res->mx_freq >= threshold )
                ans[i] = res->most_freq_val;
        }

        return ans;
    }
};

// not going to combine if not needed from the get cuts runtime in half, but still too slow
// adding caching does not make an additional difference
/*
...
    unordered_map<long long, T> mem;

    // range query (sum)
    T get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return T();
        if (l == tl && r == tr)
            return t[v];

        long long key = (((long long)tl)<<42) + (((long long)tr)<<28) + (((long long)l)<<14) + (long long)r;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        int tm = (tl + tr) / 2;
        if( l > min(r, tm) )
            return mem[key] = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        if( max(l, tm+1) > r )
            return mem[key] = lft;
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return mem[key] = combine(lft, rgt);
    }
...
*/
