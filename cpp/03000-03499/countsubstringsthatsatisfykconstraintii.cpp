
// 3261. Count Substrings That Satisfy K-Constraint II
// https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/






class Solution {
private:

    long long solve(string& s, int k, int b, int e) {
        long long l = e - b + 1;

        long long ret = 0;

        int cnt0 = 0;
        int cnt1 = 0;

        // sliding window
        long long last_start = b;
        long long i = b;
        for(long long j = b; j <= e; ++j) {
            if( s[j] == '0' )
                ++cnt0;
            else
                ++cnt1;

            if( cnt0 > k && cnt1 > k ) {
                // cout << "window i " << i << " j " << j << endl;

                // right factor
                long long rf = (e+1)-j;

                while( cnt0 > k && cnt1 > k ) {
                    if( s[i] == '0' )
                        --cnt0;
                    else
                        --cnt1;
                    ++i;
                }
                // cout << "window i " << i << " j " << j << endl;

                // left factor
                long long lf = i - last_start;

                // cout << "last_start " << last_start << " left factor " << lf << " right factor " << rf << endl;

                ret = ret + (lf * rf);

                last_start = i;
            }

        }

        // ret is the number of unusable subarrays
        // answer is total number of subarrays minus number of unusable subarrays

        return l * (l+1LL)/2LL - ret;
    }

    // Binary Indexed Tree (BIT) Fenwick Tree, 1 indexed, range update (addition), range query (sum)
    // https://cp-algorithms.com/data_structures/fenwick.html#3-range-update-and-range-query
    long long B1[100001];
    long long B2[100001];
    int n;

    void add(long long b[], int idx, long long x) {
        while( idx <= n ) {
            b[idx] += x;
            idx += idx & -idx;
        }
    }

    // range update (addition)
    void range_add(int l, int r, long long x) {
        add(B1, l, x);
        add(B1, r+1, -x);
        add(B2, l, x*(l-1));
        add(B2, r+1, -x*r);
    }

    long long sum(long long b[], int idx) {
        long long total = 0LL;
        while( idx > 0 ) {
            total += b[idx];
            idx -= idx & -idx;
        }
        return total;
    }

    long long prefix_sum(int idx) {
        return sum(B1, idx)*idx -  sum(B2, idx);
    }

    // range query (sum)
    long long range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l-1);
    }


public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        n = s.size();
        int q_sz = queries.size();

        vector<long long> ans(q_sz);

        /*
        // brute force
        for(int i = 0; i < q_sz; ++i)
            ans[i] = solve(s, k, queries[i][0], queries[i][1]);
        */

        // sliding window
        long long end[n];    // number of good subarrays ending at i
        int cnt0 = 0;
        int cnt1 = 0;
        int i = n-1;         // left index
        int j = n-1;         // right index
        for(; i >= 0; --i) {
            if( s[i] == '0' )
                ++cnt0;
            else
                ++cnt1;

            while( cnt0 > k && cnt1 > k ) {
                // cout << "window i+1 " << i+1 << " j " << j << endl;

                long long l = j - i;
                end[j] = l;

                if( s[j] == '0' )
                    --cnt0;
                else
                    --cnt1;
                --j;
            }
        }
        // finish up
        while( j >= 0 ) {
            // cout << "window i+1 " << i+1 << " j " << j << endl;
            long long l = j+1;
            end[j] = l;
            --j;
        }
        /*
        for(int k = 0; k < n; ++k)
            cout << end[k] << " ";
        cout << endl;
        */

        // if we sort our queries by ending index asc
        // then we can keep track of the number of subarrays started as keep going from left to right
        // because we have not created any subarrays beyond the ending index where we are,
        // we can query the sum of started indexes ending at our current index

        for(int k = 0; k < q_sz; ++k)
            queries[k].push_back(k);

        sort(queries.begin(),queries.end(),[](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });


        memset(B1,0,sizeof B1);
        memset(B2,0,sizeof B2);

        j = 0;
        for(int k = 0; k < q_sz; ++k) {

            int b = queries[k][0];
            int e = queries[k][1];
            int q = queries[k][2];

            // cout << "processing query " << q << " b " << b << " e " << e << endl;

            // process endings up to and including e
            while( j <= e ) {
                // cout << "updating range " << j - end[j] + 1 << " to " << j << endl;
                range_add((j - end[j] + 1)+1, j+1, 1);  // BIT is 1 indexed, hence +1
                ++j;
            }


            ans[q] = range_sum(b+1, e+1); // BIT is 1 indexed, hence +1
        }

        return ans;
    }
};
