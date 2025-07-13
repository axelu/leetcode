
// 3599. Partition Array to Minimize XOR
// https://leetcode.com/problems/partition-array-to-minimize-xor/description/

class Solution {
private:
    const int INF = 1073741824; // binary 31 digits 1000000000000000000000000000000

    int mem[250][251];

    int rec(vector<int>& nums, int n, int pos, int k) {
        // starting at pos, we have to make k non-empty positions

        if( mem[pos][k] != -1 )
            return mem[pos][k];

        int _xor = 0;
        if( k == 1 ) {
            for(int i = pos; i < n; ++i)
                _xor = _xor ^ nums[i];
            return mem[pos][k] = _xor;
        }

        int ret = INF;

        int max_i = n - k;
        for(int i = pos; i <= max_i; ++i) {
            _xor = _xor ^ nums[i];
            int t = max( _xor, rec(nums, n, i+1, k-1));
            ret = min(ret, t);
        }

        return mem[pos][k] = ret;
    }
public:
    int minXor(vector<int>& nums, int k) {
        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, k);
    }
};
