
// 3739. Count Subarrays With Majority Element II
// https://leetcode.com/problems/count-subarrays-with-majority-element-ii/

// implementation with binary indexed tree (fenwick tree)

class Solution {
private:
    vector<long long> bit; // binary indexed tree, 0-indexed, range query (sum), point update (addition)

    long long sum(int r) {
        long long ret = 0LL;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, long long delta) {
        int n = bit.size();
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(); // 1 <= n <= 1e5
        // 1 <= nums[i] <= 1e9
        // 1 <= target <= 1e9

        long long ans = 0LL;

        // example
        // let x mark an element where nums[i] == target
        // let us assume we are standing at index n-1
        // * marks end of a subarray in which target is the majority element
        //              0  1  2  3  4  5  6  7  8  9
        //              x  -  -  x  x  x  x  -  -  x
        //              *  *  *  *  *  *           *
        // length       10 9  8  7  6  5  4  3  2  1 from n-1
        // count target 6  5  5  5  4  3  2  1  1  1 from n-1
        //              1 -1 -1  1  1  1  1 -1 -1  1
        // prefixSum    0  1  0 -1  0  1  2  3  2  1  2
        // observation
        // if we convert nums[i] = 1 where nums[i] == target otherwise -1
        // and then make a prefix sum, we can count all occurences
        // of a strictly smaller prefix sums seen so far

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        map<long long,int> mp; // key: unique prefixSum value: prefixSum idx
        mp.insert({0LL, -1});
        for(int i = 1; i <= n; ++i) {
            nums[i-1] = nums[i-1] == target ? 1 : -1;
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];
            mp.insert({prefixSum[i], -1});
        }
        int unique_prefixsums = 0;
        for(auto& p: mp)
            p.second = unique_prefixsums++;

        // we will use a binary indexed tree, all nodes initialized to 0
        // each position of the tree represent the ordered list of unique prefix sums
        bit.assign(unique_prefixsums, 0LL);
        // set that we have seen prefixSum 0
        int idx = mp[0LL];
        add(idx, 1LL);

        for(int i = 1; i <= n; ++i) {
            long long ps = prefixSum[i];
            idx = mp[ps];
            // count the strictly smaller prefixSums we have seen
            ans += sum(idx-1);
            // add to the count of the current prefix sum
            add(idx, 1LL);
        }

        return ans;
    }
};



// implementation with segment tree

class Solution {
private:
    long long t[400004]; // segment tree (sum), lazy propagation, range addition, range query
    long long lazy[400004];

    void push(int v) {
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0LL;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, long long addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = query(v*2, tl, tm, tl, tm) + query(v*2+1, tm+1, tr, tm+1, tr);
        }
    }

    // get sum
    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0LL;
        if (l == tl && tr == r)
            return t[v] + ((1 + tr - tl) * lazy[v]);
        int tm = (tl + tr) / 2;
        return (1 + r - l) * lazy[v] +
               query(v*2, tl, tm, l, min(r, tm)) +
               query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(); // 1 <= n <= 1e5
        // 1 <= nums[i] <= 1e9
        // 1 <= target <= 1e9

        long long ans = 0LL;

        // example
        // let x mark an element where nums[i] == target
        // let us assume we are standing at index n-1
        // * marks end of a subarray in which target is the majority element
        //              0  1  2  3  4  5  6  7  8  9
        //              x  -  -  x  x  x  x  -  -  x
        //              *  *  *  *  *  *           *
        // length       10 9  8  7  6  5  4  3  2  1 from n-1
        // count target 6  5  5  5  4  3  2  1  1  1 from n-1
        //              1 -1 -1  1  1  1  1 -1 -1  1
        // prefixSum    0  1  0 -1  0  1  2  3  2  1  2
        // observation
        // if we convert nums[i] = 1 where nums[i] == target otherwise -1
        // and then make a prefix sum, we can count all occurences
        // of a strictly smaller prefix sums seen so far

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        map<long long,int> mp; // key: unique prefixSum value: prefixSum idx
        mp.insert({0LL, -1});
        for(int i = 1; i <= n; ++i) {
            nums[i-1] = nums[i-1] == target ? 1 : -1;
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];
            mp.insert({prefixSum[i], -1});
        }
        int unique_prefixsums = 0;
        for(auto& p: mp)
            p.second = unique_prefixsums++;

        // we will use a segment tree, all nodes initialized to 0
        // the leaves of the tree represent the ordered list of unique prefix sums
        memset(t,0,sizeof t);
        memset(lazy,0,sizeof lazy);
        // set that we have seen prefixSum 0
        int idx = mp[0LL];
        update(1, 0, unique_prefixsums-1, idx, idx, 1LL);

        for(int i = 1; i <= n; ++i) {
            long long ps = prefixSum[i];
            idx = mp[ps];
            // count the strictly smaller prefixSums we have seen
            ans += query(1, 0, unique_prefixsums-1, 0, idx-1);
            // add to the count of the current prefix sum
            update(1, 0, unique_prefixsums-1, idx, idx, 1LL);
        }

        return ans;
    }
};
