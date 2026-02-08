
// 3825. Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND
// https://leetcode.com/problems/longest-strictly-increasing-subsequence-with-non-zero-bitwise-and/

class Solution {
private:
    // Longest Increasing Subsequence (LIS)
    // https://cp-algorithms.com/dynamic_programming/longest_increasing_subsequence.html
    int lengthOfLIS(vector<int> const& a) {
        int n = a.size();
        const int INF = 1e9+1;
        vector<int> d(n+1, INF);
        d[0] = -INF;

        for (int i = 0; i < n; i++) {
            int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
            if (d[l-1] < a[i] && a[i] < d[l])
                d[l] = a[i];
        }

        int ans = 0;
        for (int l = 0; l <= n; l++) {
            if (d[l] < INF)
                ans = l;
        }
        return ans;
    }

public:
    int longestSubsequence(vector<int>& nums) {
        int nums_sz = nums.size();
        if( nums_sz == 1 )
            return nums[0] != 0 ? 1 : 0;

        int ans = 0;
        for(int bit = 0; bit <= 29; ++bit) {
            vector<int> arr;
            int mask = 1<<bit;
            for(int x: nums)
                if( mask & x ) arr.push_back(x);
            if( arr.size() > ans )
                ans = max(ans, lengthOfLIS(arr));
        }
        return ans;
    }
};

// test cases
/*
[5,4,7]
[2,3,6]
[0,1]
[0,8,16,41,42]
[1]
[16,16,16,16]
[0,0,0]
[2,14,10]

[9,5,9]
[6,23,27,25,30,19]
[37,20,21,38,9,11]
[999999999,1000000000]
*/

// passes 998/1016 test cases as of 2/3/2026, then TLE
// case 999 runs locally in about ~80ms returning correct result, but obviously too slow

/*  Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND
    a subsequence can only have elements where at least one bit is
    present in all elements of that subsequence
    example [8,16,41,42]
    bit bit  0  1  2  3
    idx val  8 16 41 42
     5  32   0  0  1  1
     4  16   0  1  0  0
     3   8   1  0  1  1
     2   4   0  0  0  0
     1   2   0  0  0  1
     0   1   0  0  1  0
    the answer is 3, the "Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND"
    is 8, 41, 42; even though the array is itself strictly increasing, 16 does not have bit 3 set,
    hence it cannot be part of the increasing subsequence

    coordinate compression - collect sorted uniques (set) and give each an idx
    based on constraints we are dealing with 30bits
    we create a binary indexed tree (BIT) aka Fenwick tree for every bit that tracks scum
    we process from right to left
    for each number, we get index, then for every bit in number we query BIT for sum[index+1,r]
        where right is number of uniques-1
    while doing so, we add 1 to the BIT at index, but only if we have not seen number yet
    worst case: all numbers unique -> 30 BITs with 100000 length each

 */
class Solution {
private:
    vector<vector<int>> t; // segment tree memory efficient indexing, max, max range query, pos update

    long long get_max(int bitidx, int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[bitidx][v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(bitidx, v+1, tl, tm, l, min(r, tm)),
                   get_max(bitidx, v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int bitidx, int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            t[bitidx][v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(bitidx, v+1, tl, tm, pos, new_val);
            else
                update(bitidx, v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[bitidx][v] = max(t[bitidx][v+1],t[bitidx][v+2*(tm-tl+1)]);
        }
    }

    map<int,int> mp; // val, idx
    int n;

    void insert(int x, int lis) {
        int idx = mp[x];
        // cout << "insert x " << x << " idx " << idx << endl;
        int bitidx = 0;
        // TODO ideally for a given x we know the set bits
        // and only iterate those instead of all till maxbit
        // we could collect that info lazyly
        while(x) {
            if( x & 1 ) {
                update(bitidx, 1, 0, n-1, idx, lis);
            }
            x >>= 1;
            ++bitidx;
        }
        return;
    }

public:
    int longestSubsequence(vector<int>& nums) {
        int nums_sz = nums.size();
        if( nums_sz == 1 )
            return nums[0] != 0 ? 1 : 0;

        set<int> unique;
        for(int val: nums)
            unique.insert(val);
        n = 0;
        for(int val: unique)
            mp.insert({val, n++});
        if( n == 1 )
            return mp.begin()->first != 0 ? 1 : 0;

        int ans = 1;
        t.assign(30, vector<int>(2*n, 0));
        stack<int> stck; // monotonically increase stack (top is largest)
        stck.push(nums[nums_sz-1]);
        int max_inserted = 0;
        for(int i = nums_sz-2; i >= 0; --i) {
            // cout << "i " << i << " nums[i] " << nums[i] << endl;
            int x = nums[i];
            if( x == 0 )
                continue;

            if( !stck.empty() ) {
                if( x > stck.top() && x > max_inserted ) {
                    // cout << "i " << i << " nums[i] " << nums[i] << " adding to stack" << endl;
                    stck.push(x);
                } else if( x == stck.top() ) {
                    // no op
                } else { // x < stck.top()
                    // we need to process elements in our stack
                    max_inserted = max(max_inserted, stck.top());
                    while( !stck.empty() && x <= stck.top() ) {
                        int val = stck.top();
                        stck.pop();
                        if( x == val )
                            break;
                        // as of the time we encountered this val, there
                        // was no greater val, hence insert w/ length LIS = 1
                        insert(val, 1);
                    }
                }
            } else { // stck.empty()
                if( x > max_inserted ) {
                    // cout << "i " << i << " nums[i] " << nums[i] << " adding to stack" << endl;
                    stck.push(x);
                }
            }
            if( max_inserted > x ) {
                int idx = mp[x];
                int bitidx = 0;
                // TODO ideally for a given x we know the bits
                // and only iterate those instead of all till maxbit
                // we could collect that info lazyly
                while(x) {
                    if( x & 1 ) {
                        int res = get_max(bitidx, 1, 0, n-1, idx+1, n-1);
                        // cout << "i " << i << " nums[i] " << nums[i] << " idx " << idx;
                        // cout << " bitidx " << bitidx << " res " << res << endl;

                        ans = max(ans, res+1);
                        update(bitidx, 1, 0, n-1, idx, res+1);
                    }
                    x >>= 1;
                    ++bitidx;
                }
            }
            // cout << "i " << i << " nums[i] " << nums[i] << " ans " << ans << endl;
        }

        return ans;
    }
};

// brute force, not submitted
class Solution {
private:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 ) return 0;

        // length of longest increasing subsequence encountered ending at idx i
        // init to length of 1 at every index as there is at least the element iteself
        int dp[n];
        for(int i = 0; i < n; ++i) dp[i] = 1;

        int llis = 1; // length of longest increasing subsequence encountered

        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if( nums[i] > nums[j] ) {
                    // record length of longest increasing subsequence
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            llis = max(llis, dp[i]); // keep track of lis ever encountered
        }

        return llis;
    }

public:
    int longestSubsequence(vector<int>& nums) {
        int nums_sz = nums.size();
        if( nums_sz == 1 )
            return nums[0] != 0 ? 1 : 0;

        int ans = 0;
        for(int bit = 0; bit <= 29; ++bit) {
            vector<int> arr;
            int mask = 1<<bit;
            for(int x: nums)
                if( mask & x ) arr.push_back(x);
            if( arr.size() > ans )
                ans = max(ans, lengthOfLIS(arr));
        }
        return ans;
    }
};
