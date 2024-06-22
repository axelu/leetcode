
// 3109. Find the Index of Permutation
// https://leetcode.com/problems/find-the-index-of-permutation/






// initialize once
int factorial[100001];
bool init = false;

class Solution {
private:
    vector<int> bit; // binary indexed tree bit, 0 indexed
    int n;

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    const long mod = 1000000007;

public:
    int getPermutationIndex(vector<int>& perm) {
        if( !init ) {
            init = true;
            factorial[0] = 1L;
            for(long i = 1; i <= 100000; ++i)
                factorial[i] = (factorial[i-1] * i) % mod;
        }

        n = perm.size();

        // init bit
        bit.assign(n,0);
        for(int i = 0; i < n; ++i)
            add(i, 1);

        long ans = 0;
        for(int i = 0; i < n; ++i) {
            // we need to find out that position of nums[i] among the remaining integers
            int k = sum(perm[i]-1); // -1 because binary indexed tree is 0-indexed
            ans = (ans + (((long)(k-1) * factorial[(n-1)-i]) % mod)) % mod;
            add(perm[i]-1, -1);
        }

        return ans;
    }
};
