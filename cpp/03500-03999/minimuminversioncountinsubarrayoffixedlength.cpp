
// 3768. Minimum Inversion Count in Subarrays of Fixed Length
// https://leetcode.com/problems/minimum-inversion-count-in-subarrays-of-fixed-length/



class Solution {
private:
    vector<int> bit;  // binary indexed tree, 0-indexed, range query (sum), point update (add/subtract)
    int n;

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    long long minInversionCount(vector<int>& nums, int k) {
        int nums_sz = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e9; 1 <= k <= n
        if( k == 1 )
            return 0;

        // idea
        //
        // let k = 5
        //  ---------
        //  0 1 2 3 4 5 6 7 8 9
        //  2 1 3 5 1 1
        //  for subarray [0..4] we have 4 inversion pairs
        //  by index: 0,1; 0,4; 2,4; 3,4
        //  we then slide our subarray to the right
        //    ---------
        //  0 1 2 3 4 5 6 7 8 9
        //  2 1 3 5 1 1
        //  we 1st remove the number pairs we counted for index 0: 2
        //    as we are removing alwoays the 1st index of out subarray,
        //    we can count all occurences of values strictly smaller
        //  we then add new number of pairs we are gaining when adding index 5: 2
        //    as we are alway adding the last index,
        //    we can count all occurences of values strictly greater
        //  so we have 4 inversion pairs
        // as nums[i] can be larger, we will use index compression

        set<int> st;
        for(int x: nums)
            st.insert(x);

        unordered_map<int,int> dic; // key: val; value: index
        n = 1; // for simplicity adding sentinel on left
        for(int x: st)
            dic[x] = n++;
        ++n; // sentinel on the right

        // we will use a binary indexed tree, all nodes initialized to 0
        bit.assign(n, 0);

        // build the initial subarray [0..k-1] from right to left
        long long ip = 0LL; // inversion pairs
        for(int i = k-1; i >= 0; --i) {
            int idx = dic[nums[i]];
            // we have already added items to the right
            // aka items where i is greater
            // so we need to count all smaller
            ip += (long long)sum(0, idx-1);

            add(idx, 1);
        }

        long long ans = ip;

        // sliding window
        int i = 0; // left index
        for(int j = k-1; j+1 < nums_sz;) {
            // remove index i
            int idx = dic[nums[i]];
            ip -= (long long)sum(0, idx-1);
            add(idx, -1);
            ++i;

            // add index j+1
            ++j;
            idx = dic[nums[j]];
            ip += (long long)sum(idx+1, n-1);
            add(idx, 1);

            ans = min(ans, ip);
        }

        return ans;
    }
};
