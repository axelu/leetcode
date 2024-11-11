
// 3277. Maximum XOR Score Subarray Queries
// https://leetcode.com/problems/maximum-xor-score-subarray-queries/

class Solution {
private:
    void printvector(vector<int>& nums) {
        for(int x: nums)
            cout << x << " ";
        cout << endl;
    }

    int xorscore(vector<int>& nums, int s, int e) {
        if( s == e )
            return nums[s];

        int ret = 0;

        int cur[2000];

        // round0
        for(int i = s, k = 0; i < e; ++i, ++k)
            cur[k] = nums[i] ^ nums[i+1];

        int n = e - s;
        while( n > 1 ) {
            for(int i = 0; i < n-1; ++i)
                cur[i] = cur[i] ^ cur[i+1];
            --n;
        }

        return cur[0];
    }

    int t[4000]; // segment tree memory efficient indexing

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            // t[v] = new_val;
            t[v] = max(t[v], new_val); // !!! only update if greater
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        int q_sz = queries.size();
        vector<int> ans(q_sz);

        // idea:
        // sort the questions by length
        // build a max segment tree from nums
        // answer all questions of length 1
        // do a round of XOR
        // update the the tree (point update) but only if new value is greater
        // answer all questions of length 2

        /*
        vector<vector<int>> qs[n+1];
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][1] - queries[i][0] + 1;
            qs[l].push_back({queries[i][0], queries[i][1], i});
        }

        build(nums, 1, 0, n-1);
        for(int i = 1; i <= n; ++i) {
            // cout << "length i " << i << endl;
            // our tree holds the answer for subarrays of length i

            // answer questions of length i and greater

            for(int j = i; j <= n; ++j) {

                for(int k = 0; k < qs[j].size(); ++k) {
                    int l = qs[j][k][0];
                    int r = qs[j][k][1];
                    int q_idx = qs[j][k][2];

                    // adjust r
                    r = r - i + 1;
                    int t = get_max(1, 0, n-1, l, r);

                    ans[q_idx] = max(ans[q_idx], t);
                }
            }


            // do calc for next round
            for(int j = 0; j < n-i; ++j) {
                nums[j] = nums[j] ^ nums[j+1];
                update(1, 0, n-1, j, nums[j]);
                // cout << nums[j] << " ";
            }
            // cout << endl;

        }
        */

        // change approach
        // sort queries by right index
        // calculate up to right index
        // answer questions
        // repeat

        vector<vector<int>> qs[n];
        for(int i = 0; i < q_sz; ++i)
            qs[queries[i][1]].push_back({queries[i][0], queries[i][1], i});

        build(nums, 1, 0, n-1);
        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << endl;
            // printvector(nums);

            // answer questions at right index i
            for(int k = 0; k < qs[i].size(); ++k) {
                int l = qs[i][k][0];
                int r = qs[i][k][1];
                int q_idx = qs[i][k][2];
                ans[q_idx] = get_max(1, 0, n-1, l, r);
            }
            // do calc for next round
            if( i < n-1 ) {
                for(int j = i+1; j > 0; --j) {
                    nums[j-1] = nums[j-1] ^ nums[j];
                    update(1, 0, n-1, j-1, nums[j-1]);
                }
            }
        }

        return ans;
    }
};



// passes 629/635 tests as of 9/25/2024, then TLE

class Solution {
private:
    int xorscore(vector<int>& nums, int s, int e) {
        if( s == e )
            return nums[s];

        int ret = 0;

        int cur[2000];

        // round0
        for(int i = s, k = 0; i < e; ++i, ++k)
            cur[k] = nums[i] ^ nums[i+1];

        int n = e - s;
        while( n > 1 ) {
            for(int i = 0; i < n-1; ++i)
                cur[i] = cur[i] ^ cur[i+1];
            --n;
        }

        return cur[0];
    }

    int t[4000]; // segment tree memory efficient indexing

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            // t[v] = new_val;
            t[v] = max(t[v], new_val); // !!! only update if greater
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {

        // idea:
        // sort the questions by length
        // build a max segment tree from nums
        // answer all questions of length 1
        // do a round of XOR
        // update the the tree (point update) but only if new value is greater
        // answer all questions of length 2

        int n = nums.size();

        vector<vector<int>> qs[n+1];
        int q_sz = queries.size();
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][1] - queries[i][0] + 1;
            qs[l].push_back({queries[i][0], queries[i][1], i});
        }

        vector<int> ans(q_sz);

        build(nums, 1, 0, n-1);
        for(int i = 1; i <= n; ++i) {
            // cout << "length i " << i << endl;
            // our tree holds the answer for subarrays of length i

            // answer questions of length i and greater
            for(int j = i; j <= n; ++j) {

                for(int k = 0; k < qs[j].size(); ++k) {
                    int l = qs[j][k][0];
                    int r = qs[j][k][1];
                    int q_idx = qs[j][k][2];

                    // adjust r
                    r = r - i + 1;
                    int t = get_max(1, 0, n-1, l, r);

                    ans[q_idx] = max(ans[q_idx], t);
                }
            }

            // do calc for next round
            for(int j = 0; j < n-i; ++j) {
                nums[j] = nums[j] ^ nums[j+1];
                update(1, 0, n-1, j, nums[j]);
                // cout << nums[j] << " ";
            }
            // cout << endl;

        }

        return ans;
    }
};
