
// 3653. XOR After Range Multiplication Queries I
// https://leetcode.com/problems/xor-after-range-multiplication-queries-i/



class Solution {
private:
    long const mod = 1000000007L;
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q_sz = queries.size();

        // queries[i] = [li, ri, ki, vi]
        // worst case nums[idx] = 1e9, vi = 1e5, nums[idx] * vi = 1e14
        // ops
        //      idx = li
        //      while idx <= ri
        //          update nums[idx] = (nums[idx] * vi) % mod
        //          idx += ki

        // brute force

        for(int i = 0; i < q_sz; ++i) {
            int idx = queries[i][0];
            int r = queries[i][1];
            int k = queries[i][2];
            long v = queries[i][3];

            while( idx <= r ) {
                nums[idx] = ((long)nums[idx] * v) % mod;
                idx += k;
            }
        }

        int _xor = nums[0];
        for(int i = 1; i < n; ++i)
            _xor = _xor ^ nums[i];

        return _xor;
    }
};
